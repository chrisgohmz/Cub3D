/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:33:59 by cgoh              #+#    #+#             */
/*   Updated: 2025/04/11 22:31:31 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

static bool	load_death_sprites2(t_data *data)
{
	if (!load_sprite_texture(data->map_data.head_sprites + 8, data,
			"./textures/sprites/golden_freddy_head9.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 9, data,
			"./textures/sprites/golden_freddy_head10.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 10, data,
			"./textures/sprites/golden_freddy_head11.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 11, data,
			"./textures/sprites/golden_freddy_head12.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 12, data,
			"./textures/sprites/golden_freddy_head13.xpm"))
		return (false);
	return (true);
}

bool	load_death_sprites(t_data *data)
{
	if (!load_sprite_texture(data->map_data.head_sprites, data,
			"./textures/sprites/golden_freddy_head1.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 1, data,
			"./textures/sprites/golden_freddy_head2.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 2, data,
			"./textures/sprites/golden_freddy_head3.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 3, data,
			"./textures/sprites/golden_freddy_head4.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 4, data,
			"./textures/sprites/golden_freddy_head5.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 5, data,
			"./textures/sprites/golden_freddy_head6.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 6, data,
			"./textures/sprites/golden_freddy_head7.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 7, data,
			"./textures/sprites/golden_freddy_head8.xpm"))
		return (false);
	return (load_death_sprites2(data));
}

bool	load_door_texture(t_door *door, void *mlx, char *path)
{
	door->img = mlx_xpm_file_to_image(mlx, path,
			&door->width, &door->height);
	if (!door->img)
	{
		ft_dprintf(STDERR_FILENO, "Error\nFailed to load texture file\n");
		return (false);
	}
	door->addr = mlx_get_data_addr(door->img, &door->bits_per_pixel,
			&door->size_line, &door->endian);
	if (!door->addr)
	{
		ft_dprintf(STDERR_FILENO, "Error\nFailed to get image data"
			"address: %s\n", path);
		mlx_destroy_image(mlx, door->img);
		return (false);
	}
	return (true);
}

bool	load_wall_texture(t_wall_texture *wall, void *mlx, char *path)
{
	if (wall->img)
	{
		ft_dprintf(STDERR_FILENO, "Error\nFile contains double key\n");
		return (false);
	}
	wall->img = mlx_xpm_file_to_image(mlx, path,
			&wall->img_width, &wall->img_height);
	if (!wall->img)
	{
		ft_dprintf(STDERR_FILENO, "Error\nFailed to load texture file\n");
		return (false);
	}
	wall->addr = mlx_get_data_addr(wall->img, &wall->bits_per_pixel,
			&wall->size_line, &wall->endian);
	if (!wall->addr)
	{
		ft_dprintf(STDERR_FILENO, "Error\nFailed to get image data"
			"address: %s\n", path);
		mlx_destroy_image(mlx, wall->img);
		return (false);
	}
	return (true);
}
