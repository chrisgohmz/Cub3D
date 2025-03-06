/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:58:40 by apoh              #+#    #+#             */
/*   Updated: 2025/03/06 22:15:05 by cgoh             ###   ########.fr       */
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

static bool	get_element_info(t_mapdata *data)
{
	int	i;

	i = -1;
	while (data->elements[++i])
	{
		data->elements_info = ft_split(data->elements[i], ' ');
		if (!data->elements_info)
			return (false);
		if (count_arr_elements(data->elements_info) == 2)
		{
			if (!ft_strncmp(data->elements_info[0], NORTH, sizeof(NORTH)))
				data->north_texture = ft_strdup(data->elements_info[1]);
			else if (!ft_strncmp(data->elements_info[0], SOUTH, sizeof(SOUTH)))
				data->south_texture = ft_strdup(data->elements_info[1]);
			else if (!ft_strncmp(data->elements_info[0], EAST, sizeof(EAST)))
				data->east_texture = ft_strdup(data->elements_info[1]);
			else if (!ft_strncmp(data->elements_info[0], WEST, sizeof(WEST)))
				data->west_texture = ft_strdup(data->elements_info[1]);
			else if (!ft_strncmp(data->elements_info[0], FLOOR, sizeof(FLOOR)))
			{
				data->floor_colour = get_color(data->elements_info[1]);
				if (data->floor_colour == -1)
					return (false);	
			}
			else if (!ft_strncmp(data->elements_info[0], CEILING, sizeof(CEILING)))
			{
				data->ceiling_colour = get_color(data->elements_info[1]);
				if (data->ceiling_colour == -1)
					return (false);	
			}
			else
			{
				free_2d_arr((void ***)&data->elements_info);
				return (false);
			}
		}
		else
		{
			free_2d_arr((void ***)&data->elements_info);
			return (false);
		}
		free_2d_arr((void ***)&data->elements_info);
	}
	return (true);
}

// static int	read_map_line(t_mapdata *data->map_data)
// {
// 	char	*line;
// 	int	height;
	
// 	height = 0;
// 	data->map_data->map = malloc(sizeof(char *) * 30);
// 	if (data->map_data->map == NULL)
// 	{
// 		printf("Allocating memory for map failed\n");
// 		return (-1);
// 	}
// 	while (1)
// 	{
// 		line = get_next_line(data->map_data->fd);
// 		if (line == NULL)
// 			break ;
// 		if (ft_strncmp(line, "\n", 1) == 0)
// 		{
// 			free(line);
// 			continue ;
// 		}
// 		data->map_data->map[height] = ft_strdup(line);
// 		height++;
// 		free(line);
// 	}
// 	data->map_data->map[height] = NULL;
// 	data->map_data->map_height = height;
// 	return (0);
// }

static bool	get_map(t_data *data)
{
	size_t	width;
	
	while (data->map_data.line)
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
				return (false);
		}
		data->map_data.map_height++;
		width = ft_strlen(data->map_data.line);
		if (width > (size_t)data->map_data.map_width)
			data->map_data.map_width = width;
		data->map_data.line = get_next_line(data->map_data.fd);
	}
	data->map_data.map = ft_split(data->map_data.file_content, '\n');
	free(data->map_data.file_content);
	if (!data->map_data.map)
		return (false);
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
	if (!get_element_info(&data->map_data))
	{
		free_2d_arr((void ***)&data->map_data.elements);
		return (-1);
	}
	free_2d_arr((void ***)&data->map_data.elements);
	if (!get_map(data))
		return (-1);
	close(data->map_data.fd);
	printf("After parsing, initialising data collected\n");
	printf("North texture : %s\n", data->map_data.north_texture);
	printf("South texture : %s\n", data->map_data.south_texture);
	printf("West texture : %s\n", data->map_data.west_texture);
	printf("East texture : %s\n", data->map_data.east_texture);
	for (int i = 0; data->map_data.map[i]; i++)
	{
		printf("%s\n", data->map_data.map[i]);
		free(data->map_data.map[i]);
	}
	free(data->map_data.map);
	free(data->map_data.north_texture);
	free(data->map_data.south_texture);
	free(data->map_data.west_texture);
	free(data->map_data.east_texture);
	return (0);
}
