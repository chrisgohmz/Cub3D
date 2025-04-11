/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:45:48 by apoh              #+#    #+#             */
/*   Updated: 2025/04/11 22:32:33 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calculate_texture_x(t_render_sprites *sprites, t_data *data)
{
	sprites->tex_x = (int)(256 * (sprites->stripe - (-sprites->spritewidth / 2
					+ sprites->spritescreen_x))
			* data->map_data.sprites[sprites->i].width
			/ sprites->spritewidth) / 256;
}

int	validate_transform_y_value(t_render_sprites *sprites)
{
	if (sprites->transform_y <= 0)
	{
		sprites->i++;
		return (-1);
	}
	return (1);
}

int	process_sprite(t_render_sprites *sprites, t_data *data)
{
	calculate_sprite_transformations(sprites, data);
	if (validate_transform_y_value(sprites) == -1)
		return (-1);
	calculate_sprite_screen_position_and_size(sprites);
	return (0);
}

int	validate_stripes(t_render_sprites *sprites, t_data *data)
{
	calculate_texture_x(sprites, data);
	return (sprites->transform_y > 0
		&& sprites->stripe > 0
		&& sprites->stripe < WIDTH
		&& sprites->transform_y < data->zbuffer[sprites->stripe]);
}

void	render_pixels(t_render_sprites *sprites, t_data *data)
{
	while (sprites->y_loop < sprites->drawend_y)
	{
		calculate_texture_y(sprites, data);
		if (validate_texture_coordinates(sprites, data) == -1)
			break ;
		get_color_for_texture(sprites, data);
		sprites->y_loop++;
	}
}
