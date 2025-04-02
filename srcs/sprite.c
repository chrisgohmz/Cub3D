/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:09:41 by apoh              #+#    #+#             */
/*   Updated: 2025/03/31 21:52:46 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	sort_sprites(t_data *data)
	// Sort descending by distance
{
	t_sprite	temp;
	double		dist_i;
	double		dist_j;
	int			i;
	int			j;

	i = -1;
	while (++i < data->map_data.num_sprites - 1)
	{
		j = i + 1;
		while (j < data->map_data.num_sprites)
		{
			dist_i = pow(data->player_pos.x - data->map_data.sprites[i].x, 2)
				+ pow(data->player_pos.y - data->map_data.sprites[i].y, 2);
			dist_j = pow(data->player_pos.x - data->map_data.sprites[j].x, 2)
				+ pow(data->player_pos.y - data->map_data.sprites[j].y, 2);
			if (dist_i < dist_j)
			{
				temp = data->map_data.sprites[i];
				data->map_data.sprites[i] = data->map_data.sprites[j];
				data->map_data.sprites[j] = temp;
			}
			j++;
		}
	}
}

void	render_sprites(t_data *data)
	//skip sprites that are not seen in FOV //
	// texture x-coordinate //
{
	t_render_sprites	sprites;

	ft_memset(&sprites, 0, sizeof(t_render_sprites));
	sort_sprites(data);
	while (sprites.i < data->map_data.num_sprites)
	{
		if (process_sprite(&sprites, data) == -1)
			continue ;
		while (sprites.stripe < sprites.drawend_x)
		{
			if (sprites.stripe >= 0 && sprites.stripe < WIDTH
			&& sprites.y_loop >= 0 && sprites.y_loop < HEIGHT
			&& validate_stripes(&sprites, data))
			{
				sprites.y_loop = sprites.drawstart_y;
				render_pixels(&sprites, data);
			}
			sprites.stripe++;
		}
		sprites.i++;
	}
}
