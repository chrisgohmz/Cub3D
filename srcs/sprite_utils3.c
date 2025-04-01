/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:45:48 by apoh              #+#    #+#             */
/*   Updated: 2025/04/01 18:45:49 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calculating_texture_x_coordinates(
			t_render_sprites *sprites, t_data *data)
{
	sprites->tex_x = (int)(256 * (sprites->stripe - (-sprites->spritewidth / 2
					+ sprites->spritescreen_x))
			* data->map_data.sprites[sprites->i].width
			/ sprites->spritewidth) / 256;
}
