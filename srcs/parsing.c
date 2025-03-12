/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:58:40 by apoh              #+#    #+#             */
/*   Updated: 2025/03/10 23:15:48 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	found_map_start(const char *str)
{
	int	i;

	i = -1;
	while (str[++i] == ' ');
	return (str[i] == '1');
}

static int	count_arr_elements(char **arr)
{
	int	count;

	count = -1;
	while (arr[++count]);
	return (count);
}

static int	get_color(char *str)
{
	char	**color_rgb_arr;
	int		color;

	color_rgb_arr = ft_split(str, ',');
	if (!color_rgb_arr)
		return (-1);
	color = (ft_atoi(color_rgb_arr[0]) << 16) + (ft_atoi(color_rgb_arr[1]) << 8) + (ft_atoi(color_rgb_arr[2]));
	free_2d_arr((void ***)&color_rgb_arr);
	return (color);
}

static bool	get_texture(t_wall_texture *wall, t_data *data, char *path)
{
	wall->img = mlx_xpm_file_to_image(data->mlx, path, &wall->img_width, &wall->img_height);
	if (!wall->img)
	{
		ft_dprintf(STDERR_FILENO, "Error\nFailed to load texture file\n");
		return (false);
	}
	wall->addr = mlx_get_data_addr(wall->img, &wall->bits_per_pixel, &wall->size_line, &wall->endian);
	if (!wall->addr)
	{
		ft_dprintf(STDERR_FILENO, "Error\nFailed to get image data address: %s\n", path);
		mlx_destroy_image(data->mlx, wall->img);
		return (false);
	}
	return (true);
}

static bool	load_door_texture(t_data *data)
{
	char	*door_texture_path = "./textures/Door.xpm";
	return (get_texture(&data->map_data.door_texture, data, door_texture_path));
}

static bool	get_element_info(t_data *data)
{
	int	i;

	i = -1;
	while (data->map_data.elements[++i])
	{
		data->map_data.elements_info = ft_split(data->map_data.elements[i], ' ');
		if (!data->map_data.elements_info)
			return (false);
		if (count_arr_elements(data->map_data.elements_info) == 2)
		{
			if (!ft_strncmp(data->map_data.elements_info[0], NORTH, sizeof(NORTH)))
			{
				printf("%s\n", data->map_data.elements_info[1]);
				if (!get_texture((&(data->map_data).north_texture), data, data->map_data.elements_info[1]))
					return (false);
			}
			else if (!ft_strncmp(data->map_data.elements_info[0], SOUTH, sizeof(SOUTH)))
			{
				if (!get_texture(&data->map_data.south_texture, data, data->map_data.elements_info[1]))
					return (false);
			}
			else if (!ft_strncmp(data->map_data.elements_info[0], EAST, sizeof(EAST)))
			{
				if (!get_texture(&data->map_data.east_texture, data, data->map_data.elements_info[1]))
					return (false);
			}
			else if (!ft_strncmp(data->map_data.elements_info[0], WEST, sizeof(WEST)))
			{
				if (!get_texture(&data->map_data.west_texture, data, data->map_data.elements_info[1]))
					return (false);
			}
			else if (!ft_strncmp(data->map_data.elements_info[0], FLOOR, sizeof(FLOOR)))
			{
				data->map_data.floor_colour = get_color(data->map_data.elements_info[1]);
				if (data->map_data.floor_colour == -1)
					return (false);	
			}
			else if (!ft_strncmp(data->map_data.elements_info[0], CEILING, sizeof(CEILING)))
			{
				data->map_data.ceiling_colour = get_color(data->map_data.elements_info[1]);
				if (data->map_data.ceiling_colour == -1)
					return (false);	
			}
			else
			{
				free_2d_arr((void ***)&data->map_data.elements_info);
				return (false);
			}
		}
		else
		{
			free_2d_arr((void ***)&data->map_data.elements_info);
			return (false);
		}
		free_2d_arr((void ***)&data->map_data.elements_info);
	}
	return (true);
}

static bool	get_map(t_data *data)
{
	size_t	width;
	int	y;
	int	x;
	
	y = 0;
	x = 0;
	while (data->map_data.line)
	{
		if (!data->map_data.file_content)
			data->map_data.file_content = ft_strdup(data->map_data.line);
		else
		{
			data->map_data.tmp = data->map_data.file_content;
			data->map_data.file_content = ft_strjoin(data->map_data.file_content, data->map_data.line);
			free(data->map_data.tmp);
		}
		if (!data->map_data.file_content)
				return (false);
		data->map_data.map_height++;
		width = ft_strlen(data->map_data.line);
		if (width > (size_t)data->map_data.map_width)
			data->map_data.map_width = width;
		free(data->map_data.line);
		data->map_data.line = get_next_line(data->map_data.fd);
	}
	data->map_data.map = ft_split(data->map_data.file_content, '\n');
	free(data->map_data.file_content);
	if (!data->map_data.map)
		return (false);
	while (y < data->map_data.map_height)
	{
		while (x < data->map_data.map_width)
		{
			if (data->map_data.map[y][x] == 'D')
			{
				data->map_data.door_x = x;
				data->map_data.door_y = y;
				return (true);
			}
			x++;
		}
		y++;
	}
	return (true);
}

int	parsing(t_data *data, char *file_path)
{	
	ft_bzero(&data->map_data, sizeof(t_mapdata));
	data->map_data.fd = open(file_path, O_RDONLY);
	if (data->map_data.fd == -1)
	{
		printf("File opening failed\n");
		return (-1);
	}
	data->map_data.line = get_next_line(data->map_data.fd);
	while (data->map_data.line && !found_map_start(data->map_data.line))
	{
		if (!data->map_data.file_content)
			data->map_data.file_content = data->map_data.line;
		else
		{
			data->map_data.tmp = data->map_data.file_content;
			data->map_data.file_content = ft_strjoin(data->map_data.file_content, data->map_data.line);
			free(data->map_data.tmp);
			free(data->map_data.line);
			if (!data->map_data.file_content)
				return (-1);
		}
		data->map_data.line = get_next_line(data->map_data.fd);
	}
	data->map_data.elements = ft_split(data->map_data.file_content, '\n');
	free(data->map_data.file_content);
	data->map_data.file_content = NULL;
	if (!data->map_data.elements)
		return (-1);
	if (!get_element_info(data))
	{
		free_2d_arr((void ***)&data->map_data.elements);
		return (-1);
	}
	free_2d_arr((void ***)&data->map_data.elements);
	if (!get_map(data))
		return (-1);
	if (!load_door_texture(data))
		return (-1);
	close(data->map_data.fd);
	return (0);
}
