/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:03:35 by apoh              #+#    #+#             */
/*   Updated: 2025/03/28 14:03:37 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	get_element_info(t_data *data)
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
				if (!get_texture((&(data->map_data).north_texture), data,
					data->map_data.elements_info[1]))
					return (free_2d_arr((void ***)&data->map_data.elements_info), false);
			}
			else if (!ft_strncmp(data->map_data.elements_info[0], SOUTH, sizeof(SOUTH)))
			{
				if (!get_texture(&data->map_data.south_texture, data,
					data->map_data.elements_info[1]))
					return (free_2d_arr((void ***)&data->map_data.elements_info), false);
			}
			else if (!ft_strncmp(data->map_data.elements_info[0], EAST, sizeof(EAST)))
			{
				if (!get_texture(&data->map_data.east_texture, data,
					data->map_data.elements_info[1]))
					return (free_2d_arr((void ***)&data->map_data.elements_info), false);
			}
			else if (!ft_strncmp(data->map_data.elements_info[0], WEST, sizeof(WEST)))
			{
				if (!get_texture(&data->map_data.west_texture, data,
					data->map_data.elements_info[1]))
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
	if (check_for_NSEW_textures(data) == false || check_for_FC_textures(data) == false)
		return (false);
	return (true);
}

bool	check_wall_surround(t_mapdata *map_data, char **map_copy, int x, int y)
{
	if (y < 0 || y >= map_data->map_height || x < 0
		|| map_copy[y][x] == ' ' || !map_copy[y][x])
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

bool	check_map_valid(t_data *data)
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
		ft_memcpy(map_copy[i], data->map_data.map[i],
			ft_strlen(data->map_data.map[i]) + 1);
	}
	if (!check_wall_surround(&data->map_data, map_copy, data->player_pos.x,
			data->player_pos.y))
	{
		ft_dprintf(STDERR_FILENO, "Error\nMap is not enclosed with walls\n");
		free_2d_arr((void ***)&map_copy);
		return (false);
	}
	free_2d_arr((void ***)&map_copy);
	return (true);
}

void	setting_up_player_direction(t_data *data, int x, int y)
{
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
}

void	get_player_pos_direction(t_data *data)
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
				setting_up_player_direction(data, x, y);
				return ;
			}
		}
	}
}
