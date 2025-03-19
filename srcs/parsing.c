/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:58:40 by apoh              #+#    #+#             */
/*   Updated: 2025/03/19 15:05:42 by cgoh             ###   ########.fr       */
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

static bool	check_color_range(int *color, char *color_str)
{
	int	i;

	if (ft_strlen(color_str) > 3)
	{
		ft_dprintf(STDERR_FILENO, "Error\nColor range must be within 0 and 255\n");
		return (false);
	}
	i = -1;
	while (color_str[++i])
	{
		if (!ft_isdigit(color_str[i]))
		{
			ft_dprintf(STDERR_FILENO, "Error\nColor may only contain digits\n");
			return (false);
		}
	}
	*color = ft_atoi(color_str);
	if (*color < 0 || *color > 255)
	{
		ft_dprintf(STDERR_FILENO, "Error\nColor range must be within 0 and 255\n");
		return (false);
	}
	return (true);
}

static int	count_commas(const char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == ',')
			++count;
	}
	return (count);
}

static int	get_color(char *str)
{
	char	**color_rgb_arr;
	int		red;
	int		green;
	int		blue;

	if (count_commas(str) != 2)
	{
		ft_dprintf(STDERR_FILENO, "Error\nFile contains invalid line\n");
		return (-1);
	}
	color_rgb_arr = ft_split(str, ',');
	if (!color_rgb_arr)
		return (-1);
	if (count_arr_elements(color_rgb_arr) != 3)
	{
		ft_dprintf(STDERR_FILENO, "Error\nFile contains invalid line\n");
		free_2d_arr((void ***)&color_rgb_arr);
		return (-1);
	}
	if (!check_color_range(&red, color_rgb_arr[0])
		|| !check_color_range(&green, color_rgb_arr[1])
		|| !check_color_range(&blue, color_rgb_arr[2]))
	{
		free_2d_arr((void ***)&color_rgb_arr);
		return (-1);
	}
	free_2d_arr((void ***)&color_rgb_arr);
	return ((red << 16) + (green << 8) + blue);
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

	data->map_data.ceiling_colour = -1;
	data->map_data.floor_colour = -1;
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
				if (!get_texture((&(data->map_data).north_texture), data, data->map_data.elements_info[1]))
					return (free_2d_arr((void ***)&data->map_data.elements_info), false);
			}
			else if (!ft_strncmp(data->map_data.elements_info[0], SOUTH, sizeof(SOUTH)))
			{
				if (!get_texture(&data->map_data.south_texture, data, data->map_data.elements_info[1]))
					return (free_2d_arr((void ***)&data->map_data.elements_info), false);
			}
			else if (!ft_strncmp(data->map_data.elements_info[0], EAST, sizeof(EAST)))
			{
				if (!get_texture(&data->map_data.east_texture, data, data->map_data.elements_info[1]))
					return (free_2d_arr((void ***)&data->map_data.elements_info), false);
			}
			else if (!ft_strncmp(data->map_data.elements_info[0], WEST, sizeof(WEST)))
			{
				if (!get_texture(&data->map_data.west_texture, data, data->map_data.elements_info[1]))
					return (free_2d_arr((void ***)&data->map_data.elements_info), false);
			}
			else if (!ft_strncmp(data->map_data.elements_info[0], FLOOR, sizeof(FLOOR)))
			{
				data->map_data.floor_colour = get_color(data->map_data.elements_info[1]);
				if (data->map_data.floor_colour == -1)
					return (free_2d_arr((void ***)&data->map_data.elements_info), false);	
			}
			else if (!ft_strncmp(data->map_data.elements_info[0], CEILING, sizeof(CEILING)))
			{
				data->map_data.ceiling_colour = get_color(data->map_data.elements_info[1]);
				if (data->map_data.ceiling_colour == -1)
					return (free_2d_arr((void ***)&data->map_data.elements_info), false);	
			}
			else
			{
				ft_dprintf(STDERR_FILENO, "Error\nFile contains invalid line\n");
				free_2d_arr((void ***)&data->map_data.elements_info);
				return (false);
			}
		}
		else
		{
			ft_dprintf(STDERR_FILENO, "Error\nFile contains invalid line\n");
			free_2d_arr((void ***)&data->map_data.elements_info);
			return (false);
		}
		free_2d_arr((void ***)&data->map_data.elements_info);
	}
	if (!data->map_data.north_texture.img)
	{
		ft_dprintf(STDERR_FILENO, "Error\nMissing north wall texture\n");	
		return (false);
	}
	else if (!data->map_data.south_texture.img)
	{
		ft_dprintf(STDERR_FILENO, "Error\nMissing south wall texture\n");
		return (false);
	}
	else if (!data->map_data.west_texture.img)
	{
		ft_dprintf(STDERR_FILENO, "Error\nMissing west wall texture\n");
		return (false);
	}
	else if (!data->map_data.east_texture.img)
	{
		ft_dprintf(STDERR_FILENO, "Error\nMissing east wall texture\n");
		return (false);
	}
	else if (data->map_data.ceiling_colour == -1)
	{
		ft_dprintf(STDERR_FILENO, "Error\nMissing ceiling colour\n");
		return (false);
	}
	else if (data->map_data.floor_colour == -1)
	{
		ft_dprintf(STDERR_FILENO, "Error\nMissing floor colour\n");
		return (false);
	}
	return (true);
}

static bool	check_wall_surround(t_mapdata *map_data, char **map_copy, int x, int y)
{
	if (y < 0 || y >= map_data->map_height || x < 0 || map_copy[y][x] == ' ' || !map_copy[y][x])
		return (false);
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'x')
		return (true);
	map_copy[y][x] = 'x';
	if (!check_wall_surround(map_data, map_copy, x + 1, y))
		return (false);
	else if (!check_wall_surround(map_data, map_copy, x - 1, y))
		return (false);
	else if (!check_wall_surround(map_data, map_copy, x, y + 1))
		return (false);
	else if (!check_wall_surround(map_data, map_copy, x, y - 1))
		return (false);
	else if (!check_wall_surround(map_data, map_copy, x - 1, y - 1))
		return (false);
	else if (!check_wall_surround(map_data, map_copy, x - 1, y + 1))
		return (false);
	else if (!check_wall_surround(map_data, map_copy, x + 1, y - 1))
		return (false);
	else if (!check_wall_surround(map_data, map_copy, x + 1, y + 1))
		return (false);
	return (true);
}

static bool	check_map_valid(t_data *data)
{
	char	**map_copy;
	int		i;
	
	map_copy = ft_calloc(data->map_data.map_height + 1, sizeof(char *));
	if (!map_copy)
		return (false);
	i = -1;
	while (++i < data->map_data.map_height)
	{
		map_copy[i] = malloc((data->map_data.map_width + 1) * sizeof(char));
		if (!map_copy[i])
			return (false);
		ft_memcpy(map_copy[i], data->map_data.map[i], ft_strlen(data->map_data.map[i]) + 1);
	}
	if (!check_wall_surround(&data->map_data, map_copy, data->player_pos.x, data->player_pos.y))
	{
		ft_dprintf(STDERR_FILENO, "Error\nMap is not enclosed with walls\n");
		free_2d_arr((void ***)&map_copy);
		return (false);
	}
	free_2d_arr((void ***)&map_copy);
	return (true);
}

static void	get_player_pos_direction(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (data->map_data.map[++y])
	{
		x = -1;
		while (data->map_data.map[y][++x])
		{
			if (ft_strchr("NSEW", data->map_data.map[y][x]))
			{
				data->player_pos.x = x + 0.5;
				data->player_pos.y = y + 0.5;
				if (data->map_data.map[y][x] == 'N')
				{
					data->player_direction.x = 0;
					data->player_direction.y = -1;
				}
				else if (data->map_data.map[y][x] == 'S')
				{
					data->player_direction.x = 0;
					data->player_direction.y = 1;
				}
				else if (data->map_data.map[y][x] == 'E')
				{
					data->player_direction.x = 1;
					data->player_direction.y = 0;
				}
				else
				{
					data->player_direction.x = -1;
					data->player_direction.y = 0;
				}
				return ;
			}
		}
	}
}

static bool	check_map_chars_valid(const char *line, bool *player_found)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (!ft_strchr("01NSEWD \n", line[i]))
		{
			ft_dprintf(STDERR_FILENO, "Error\nMap contains an invalid character\n");
			return (false);
		}
		if (ft_strchr("NSEW", line[i]))
		{
			if (!*player_found)
				*player_found = true;
			else
			{
				ft_dprintf(STDERR_FILENO, "Error\nMap must contain 1 starting position\n");
				return (false);
			}
		}
	}
	return (true);
}

static bool	get_map(t_data *data)
{
	size_t	width;
	int		y;
	int		x;
	int		door_index;
	bool	player_found;
	
	y = 0;
	x = 0;
	player_found = false;
	while (data->map_data.line)
	{
		if (!check_map_chars_valid(data->map_data.line, &player_found))
		{
			free(data->map_data.file_content);
			free(data->map_data.line);
			get_next_line(-1);
			return (false);
		}
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
	if (!player_found)
	{
		ft_dprintf(STDERR_FILENO, "Error\nMap must contain 1 starting position\n");
		free(data->map_data.file_content);
		return (false);
	}
	data->map_data.map = ft_split(data->map_data.file_content, '\n');
	free(data->map_data.file_content);
	if (!data->map_data.map)
		return (false);
	get_player_pos_direction(data);
	if (!check_map_valid(data))
		return (false);
	data->map_data.num_doors = 0;
	while (y < data->map_data.map_height)
	{
		x = -1;
		while (data->map_data.map[y][++x])
		{
			if (data->map_data.map[y][x] == 'D')
				data->map_data.num_doors++;
		}
		y++;
	}
	data->map_data.door_x = malloc(sizeof(int) * data->map_data.num_doors);
	data->map_data.door_y = malloc(sizeof(int) * data->map_data.num_doors);
	data->map_data.door_states = malloc(sizeof(bool) * data->map_data.num_doors);
	if (!data->map_data.door_x || !data->map_data.door_y || !data->map_data.door_states)
		return (false);
	y = 0;
	door_index = 0;
	while (y < data->map_data.map_height)
	{
		x = -1;
		while (data->map_data.map[y][++x])
		{
			if (data->map_data.map[y][x] == 'D')
			{
				data->map_data.door_x[door_index] = x;
				data->map_data.door_y[door_index] = y;
				data->map_data.door_states[door_index] = false;
				door_index++;
			}
		}
		y++;
	}
	if (door_index != data->map_data.num_doors)
		return (false);	
	return (true);
}

int	parsing(t_data *data, char *file_path)
{	
	ft_bzero(&data->map_data, sizeof(t_mapdata));
	data->map_data.fd = open(file_path, O_RDONLY);
	if (data->map_data.fd == -1)
	{
		ft_dprintf(STDERR_FILENO, "Error\nFailed to open %s\n", file_path);
		return (0);
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
				return (0);
		}
		data->map_data.line = get_next_line(data->map_data.fd);
	}
	data->map_data.elements = ft_split(data->map_data.file_content, '\n');
	free(data->map_data.file_content);
	data->map_data.file_content = NULL;
	if (!data->map_data.elements)
		return (0);
	if (!get_element_info(data))
	{
		get_next_line(-1);
		free(data->map_data.line);
		free_2d_arr((void ***)&data->map_data.elements);
		return (close(data->map_data.fd), 0);
	}
	free_2d_arr((void ***)&data->map_data.elements);
	if (!get_map(data))
		return (close(data->map_data.fd), 0);
	if (!load_door_texture(data))
		return (close(data->map_data.fd), 0);
	close(data->map_data.fd);
	return (1);
}
