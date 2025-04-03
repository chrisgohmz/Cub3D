/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_enemies.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:24:25 by apoh              #+#    #+#             */
/*   Updated: 2025/04/03 18:45:03 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	load_doors_and_enemies(t_data *data)
{
	int	x;
	int	y;
	int	door_index;
	int	sprite_index;
	
	data->map_data.door_x = malloc(sizeof(int) * data->map_data.num_doors);
	data->map_data.door_y = malloc(sizeof(int) * data->map_data.num_doors);
	data->map_data.door_states = malloc(sizeof(bool) * data->map_data.num_doors);
	if (!data->map_data.door_x || !data->map_data.door_y || !data->map_data.door_states)
		return (false);
	data->map_data.sprites = ft_calloc(data->map_data.num_sprites, sizeof(t_sprite));
	if (!data->map_data.sprites)
		return (false);
	y = 0;
	door_index = 0;
	sprite_index = 0;
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
			if (data->map_data.map[y][x] == 'M')
			{
				data->map_data.sprites[sprite_index].x = x;
				data->map_data.sprites[sprite_index].y = y;
				if (!load_sprite_texture(&data->map_data.sprites[sprite_index], data, "./textures/sprites/golden_freddy.xpm"))
					return (false);
				printf("Sprite %d initialized at (%d, %d)\n", sprite_index, x, y);
				sprite_index++;
			}
		}
		y++;
	}
	if (door_index != data->map_data.num_doors)
		return (false);
	return (true);
}

bool	load_sprite_texture(t_sprite *sprite, t_data *data, char *path)
{
	sprite->img = mlx_xpm_file_to_image(data->mlx, path,
			&sprite->width, &sprite->height);
	if (!sprite->img)
	{
		ft_dprintf(STDERR_FILENO, "Error\nFailed to load texture file: %s\n",
			path);
		return (false);
	}
	sprite->addr = mlx_get_data_addr(sprite->img, &sprite->bits_per_pixel,
			&sprite->size_line, &sprite->endian);
	if (!sprite->addr)
	{
		ft_dprintf(STDERR_FILENO, "Error\nFailed to get image data"
			"address: %s\n", path);
		mlx_destroy_image(data->mlx, sprite->img);
		return (false);
	}
	sprite->move_speed = 0.005;
	return (true);
}
