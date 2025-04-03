/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:03:35 by apoh              #+#    #+#             */
/*   Updated: 2025/04/03 18:31:13 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	if (!check_wall_surround(&data->map_data, map_copy, data->map_data.player_pos.x,
			data->map_data.player_pos.y))
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
		data->map_data.player_direction.x = 0;
		data->map_data.player_direction.y = -1;
	}
	else if (data->map_data.map[y][x] == 'S')
	{
		data->map_data.player_direction.x = 0;
		data->map_data.player_direction.y = 1;
	}
	else if (data->map_data.map[y][x] == 'E')
	{
		data->map_data.player_direction.x = 1;
		data->map_data.player_direction.y = 0;
	}
	else
	{
		data->map_data.player_direction.x = -1;
		data->map_data.player_direction.y = 0;
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
				data->map_data.player_pos.x = x + 0.5;
				data->map_data.player_pos.y = y + 0.5;
				setting_up_player_direction(data, x, y);
				return ;
			}
		}
	}
}
