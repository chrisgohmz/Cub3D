/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_doors_enemies.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:24:25 by apoh              #+#    #+#             */
/*   Updated: 2025/04/04 16:24:03 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	load_door(t_data *data, int *door_index, int x, int y)
{
	data->map_data.doors[*door_index].x = x;
	data->map_data.doors[*door_index].y = y;
	if (!load_door_texture(&data->map_data.doors[*door_index],
			data->mlx, "./textures/door/Door.xpm"))
		return (false);
	(*door_index)++;
	return (true);
}

static bool	load_enemy(t_data *data, int *sprite_index, int x, int y)
{
	data->map_data.sprites[*sprite_index].x = x;
	data->map_data.sprites[*sprite_index].y = y;
	if (!load_sprite_texture(&data->map_data.sprites[*sprite_index], data,
			"./textures/sprites/golden_freddy.xpm"))
		return (false);
	(*sprite_index)++;
	return (true);
}

static bool	allocate_memory_for_doors_and_enemies(t_mapdata *map_data)
{
	map_data->doors = ft_calloc(map_data->num_doors, sizeof(t_door));
	if (!map_data->doors)
		return (false);
	map_data->sprites = ft_calloc(map_data->num_sprites, sizeof(t_sprite));
	if (!map_data->sprites)
		return (false);
	return (true);
}

bool	load_doors_and_enemies(t_data *data)
{
	int	x;
	int	y;
	int	door_index;
	int	sprite_index;

	if (!allocate_memory_for_doors_and_enemies(&data->map_data))
		return (false);
	y = -1;
	door_index = 0;
	sprite_index = 0;
	while (++y < data->map_data.map_height)
	{
		x = -1;
		while (data->map_data.map[y][++x])
		{
			if (data->map_data.map[y][x] == 'D'
				&& !load_door(data, &door_index, x, y))
				return (false);
			if (data->map_data.map[y][x] == 'M'
				&& !load_enemy(data, &sprite_index, x, y))
				return (false);
		}
	}
	return (true);
}
