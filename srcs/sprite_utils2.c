/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:43:17 by apoh              #+#    #+#             */
/*   Updated: 2025/04/04 16:54:04 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calculate_sprite_transformations(
			t_render_sprites *sprites, t_data *data)
	// calculate relative position to player //
	// transformations for rendering //
{
	sprites->sprite_x = data->map_data.sprites[sprites->i].x
		- data->map_data.player_pos.x;
	sprites->sprite_y = data->map_data.sprites[sprites->i].y
		- data->map_data.player_pos.y;
	sprites->invdet = 1.0 / (data->map_data.camera_plane_pos.x
			* data->map_data.player_direction.y - data->map_data.player_direction.x
			* data->map_data.camera_plane_pos.y);
	sprites->transform_x = sprites->invdet * (data->map_data.player_direction.y
			* sprites->sprite_x - data->map_data.player_direction.x
			* sprites->sprite_y);
	sprites->transform_y = sprites->invdet * (-data->map_data.camera_plane_pos.y
			* sprites->sprite_x + data->map_data.camera_plane_pos.x
			* sprites->sprite_y);
}

void	calculate_sprite_screen_position_and_size(t_render_sprites *sprites)
	// calculate screen position and size of sprite //
{
	sprites->spritescreen_x = (int)((WIDTH / 2)
			* (1 + sprites->transform_x / sprites->transform_y));
	sprites->spriteheight = abs((int)(HEIGHT / (sprites->transform_y)));
	sprites->spritewidth = abs((int)(HEIGHT / sprites->transform_y));
	sprites->drawstart_y = -sprites->spriteheight / 2 + HEIGHT / 2;
	if (sprites->drawstart_y < 0)
		sprites->drawstart_y = 0;
	sprites->drawend_y = sprites->spriteheight / 2 + HEIGHT / 2;
	if (sprites->drawend_y >= HEIGHT)
		sprites->drawend_y = HEIGHT - 1;
	sprites->drawstart_x = -sprites->spritewidth / 2 + sprites->spritescreen_x;
	if (sprites->drawstart_x < 0)
		sprites->drawstart_x = 0;
	sprites->drawend_x = sprites->spritewidth / 2 + sprites->spritescreen_x;
	if (sprites->drawend_x >= WIDTH)
		sprites->drawend_x = WIDTH - 1;
	sprites->stripe = sprites->drawstart_x;
}

int	validate_texture_coordinates(t_render_sprites *sprites, t_data *data)
	//Validate texture address
	//Validate texX bounds
	// Validate texY bounds
	// Exit loop early to prevent segmentation faults
{
	if (!data->map_data.sprites[sprites->i].addr
		|| sprites->tex_x < 0
		|| sprites->tex_x >= data->map_data.sprites[sprites->i].width
		|| sprites->tex_y < 0
		|| sprites->tex_y >= data->map_data.sprites[sprites->i].height)
	{
		printf("Sprite %d failed validation: addr=%p, tex_x=%d"
			"(width=%d), tex_y=%d (height=%d), transform_y=%.2f\n",
			sprites->i, (void *)data->map_data.sprites[sprites->i].addr,
			sprites->tex_x, data->map_data.sprites[sprites->i].width,
			sprites->tex_y, data->map_data.sprites[sprites->i].height,
			sprites->transform_y);
		return (-1);
	}
	return (1);
}

void	calculate_texture_y(t_render_sprites *sprites, t_data *data)
	// texture y-cooridnate //
{
	sprites->d = (sprites->y_loop) * 256 - HEIGHT * 128
		+ sprites->spriteheight * 128;
	sprites->tex_y = ((sprites->d * data->map_data.sprites[sprites->i].height)
			/ sprites->spriteheight) / 256;
	if (sprites->tex_y < 0)
		sprites->tex_y = 0;
	else if (sprites->tex_y >= data->map_data.sprites[sprites->i].height)
		sprites->tex_y = data->map_data.sprites[sprites->i].height - 1;
}

void	get_color_for_texture(t_render_sprites *sprites, t_data *data)
	// get pixel color from texture //
	// non-transparent pixel //
{
	sprites->color = *(unsigned int *)(data->map_data.sprites[sprites->i].addr
			+ sprites->tex_y
			* data->map_data.sprites[sprites->i].size_line
			+ sprites->tex_x
			* data->map_data.sprites[sprites->i].bits_per_pixel / 8);
	if ((sprites->color & 0x00FFFFFF) != 0 && (sprites->stripe > MINIMAP_SIZE
			|| sprites->y_loop > MINIMAP_SIZE))
		ft_mlx_pixel_put(data, sprites->stripe,
			sprites->y_loop, sprites->color);
}
