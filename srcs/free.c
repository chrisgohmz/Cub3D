/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:26:55 by apoh              #+#    #+#             */
/*   Updated: 2025/04/01 20:50:37 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_textures(t_data *data)
{
	if (data->map_data.north_texture.img != NULL)
	{
		mlx_destroy_image(data->mlx, data->map_data.north_texture.img);
		data->map_data.north_texture.img = NULL;
	}
	if (data->map_data.south_texture.img != NULL)
	{
		mlx_destroy_image(data->mlx, data->map_data.south_texture.img);
		data->map_data.south_texture.img = NULL;
	}
	if (data->map_data.east_texture.img != NULL)
	{
		mlx_destroy_image(data->mlx, data->map_data.east_texture.img);
		data->map_data.east_texture.img = NULL;
	}
	if (data->map_data.west_texture.img != NULL)
	{
		mlx_destroy_image(data->mlx, data->map_data.west_texture.img);
		data->map_data.west_texture.img = NULL;
	}
	if (data->map_data.door_texture.img != NULL)
	{
		mlx_destroy_image(data->mlx, data->map_data.door_texture.img);
		data->map_data.door_texture.img = NULL;
	}
}

void	freeing_sprites(t_data *data)
{
	int	i;

	i = 0;
	if (data->map_data.sprites)
	{
		while (i < data->map_data.num_sprites)
		{
			if (data->map_data.sprites[i].img)
				mlx_destroy_image(data->mlx, data->map_data.sprites[i].img);
			i++;
		}
		free(data->map_data.sprites);
		data->map_data.sprites = NULL;
	}
	i = -1;
	while (++i < 13)
	{
		if (data->map_data.head_sprites[i].img)
			mlx_destroy_image(data->mlx, data->map_data.head_sprites[i].img);	
	}
}

void	free_others(t_data *data)
{
	if (data->img != NULL)
	{
		mlx_destroy_image(data->mlx, data->img);
		data->img = NULL;
	}
	if (data->win != NULL)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	if (data->mlx != NULL)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
	if (data->zBuffer)
		free(data->zBuffer);
	free(data->map_data.door_x);
	free(data->map_data.door_y);
	free(data->map_data.door_states);
	free_2d_arr((void ***)&data->map_data.map);
}

int	close_window(t_data *data)
{
	free_textures(data);
	freeing_sprites(data);
	free_others(data);
	exit(EXIT_SUCCESS);
}
