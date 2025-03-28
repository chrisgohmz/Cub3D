/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:24:25 by apoh              #+#    #+#             */
/*   Updated: 2025/03/28 13:24:28 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	load_sprite_texture(t_sprite *sprite, t_data *data, char *path)
{
	sprite->img = mlx_xpm_file_to_image(data->mlx, path,
			&sprite->width, &sprite->height);
	if (!sprite->img)
	{
		ft_dprintf(STDERR_FILENO, "Error\nFailed to load texture file\n");
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

bool	check_for_NSEW_textures(t_data *data)
{
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
	return (true);
}

bool	check_for_FC_textures(t_data *data)
{
	if (data->map_data.ceiling_colour == -1)
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
