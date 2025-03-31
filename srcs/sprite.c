/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:09:41 by apoh              #+#    #+#             */
/*   Updated: 2025/03/29 20:06:24 by cgoh             ###   ########.fr       */
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

	i = 0;
	while (i < data->map_data.num_sprites - 1)
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
		i++;
	}
}

void	render_sprites(t_data *data)
{
	int	i;
	double	sprite_x;
	double	sprite_y;
	double	invdet;
	double	transform_x;
	double	transform_y;
	int	spritescreen_x;
	int	spriteheight;
	int	drawstart_y;
	int	drawend_y;
	int	spritewidth;
	int	drawstart_x;
	int	drawend_x;
	int	stripe;
	int	y_loop;
	int	d;
	int	tex_x;
	int	tex_y;
	int	color;
	
	i = 0;
	sort_sprites(data);
	while (i < data->map_data.num_sprites)
	{
		// calculate relative position to player //
		sprite_x = data->map_data.sprites[i].x - data->player_pos.x;
		sprite_y = data->map_data.sprites[i].y - data->player_pos.y;

		// transformations for rendering //
		invdet = 1.0 / (data->camera_plane_pos.x * data->player_direction.y
			- data->player_direction.x * data->camera_plane_pos.y);
		transform_x = invdet * (data->player_direction.y * sprite_x
			- data->player_direction.x * sprite_y);
		transform_y = invdet * (-data->camera_plane_pos.y * sprite_x
			+ data->camera_plane_pos.x * sprite_y);
		if (transform_y <= 0) //skip sprites that are not seen in FOV //
		{
			printf("Transform_y is less than or equal to 0\n");
			i++;
			continue ;
		}
		// calculate screen position and size of sprite //
		spritescreen_x = (int)((WIDTH / 2) * (1 + transform_x / transform_y));
		spriteheight = abs((int)(HEIGHT / (transform_y)));
		spritewidth = abs((int)(HEIGHT / transform_y));
		drawstart_y = -spriteheight / 2 + HEIGHT / 2;
		if (drawstart_y < 0)
			drawstart_y = 0;
		drawend_y = spriteheight / 2 + HEIGHT / 2;
		if (drawend_y >= HEIGHT)
			drawend_y = HEIGHT - 1;
		drawstart_x = -spritewidth / 2 + spritescreen_x;
		if (drawstart_x < 0)
			drawstart_x = 0;
		drawend_x = spritewidth / 2 + spritescreen_x;
		if (drawend_x >= WIDTH)
			drawend_x = WIDTH - 1;
		stripe = drawstart_x;
		while (stripe < drawend_x)
		{
			// texture x-coordinate //
			tex_x = (int)(256 * (stripe - (-spritewidth / 2 + spritescreen_x))
				* data->map_data.sprites[i].width / spritewidth) / 256;
			
			if (transform_y > 0 && stripe > 0 && stripe < WIDTH
				&& transform_y < data->zBuffer[stripe])
			{
				y_loop = drawstart_y;
				while (y_loop < drawend_y)
				{
					d = (y_loop) * 256 - HEIGHT * 128 + spriteheight * 128;
					// texture y-cooridnate //
					tex_y = ((d * data->map_data.sprites[i].height)
						/ spriteheight) / 256;
					if (tex_y < 0)
						tex_y = 0;
					else if (tex_y >= data->map_data.sprites[i].height)
						tex_y = data->map_data.sprites[i].height - 1;
					if (!data->map_data.sprites[i].addr //Validate texture address
					|| tex_x < 0
					|| tex_x >= data->map_data.sprites[i].width//Validate texX bounds
					|| tex_y < 0
					|| tex_y >= data->map_data.sprites[i].height) // Validate texY bounds
					{
						printf("Sprite %d failed validation: addr=%p, tex_x=%d (width=%d), tex_y=%d (height=%d), transform_y=%.2f\n", i, (void *)data->map_data.sprites[i].addr, tex_x, data->map_data.sprites[i].width, tex_y, data->map_data.sprites[i].height, transform_y);
						break ; // Exit loop early to prevent segmentation faults
					}
					// get pixel color from texture //
					color = *(unsigned int *)(data->map_data.sprites[i].addr
					+ tex_y * data->map_data.sprites[i].size_line +
					tex_x * data->map_data.sprites[i].bits_per_pixel / 8);
					if ((color & 0x00FFFFFF) != 0
					&& (stripe > MINIMAP_SIZE || y_loop > MINIMAP_SIZE)) // non-transparent pixel //
						ft_mlx_pixel_put(data, stripe, y_loop, color);
					y_loop++;
				}
			}
			stripe++;
		}
		i++;
	}
	if (distance < 4)
	{
		if (distance > 0.1)
		{
			move_x = (data->player_pos.x - data->map_data.sprites[i].x)
				/ distance * data->map_data.sprites[i].move_speed;
			move_y = (data->player_pos.y - data->map_data.sprites[i].y)
				/ distance * data->map_data.sprites[i].move_speed;
			new_x = data->map_data.sprites[i].x + move_x;
			new_y = data->map_data.sprites[i].y + move_y;
			if (new_x >= 1 && new_x < data->map_data.map_width - 1
			&& data->map_data.map[(int)data->map_data.sprites[i].y][(int)new_x] != '1')
				data->map_data.sprites[i].x = new_x;
			if (new_y >= 1 && new_y < data->map_data.map_height - 1
			&& data->map_data.map[(int)new_y][(int)data->map_data.sprites[i].x] != '1')
				data->map_data.sprites[i].y = new_y;
			if (fabs(data->player_pos.x - data->map_data.sprites[i].x) < 0.1 &&
			fabs(data->player_pos.y - data->map_data.sprites[i].y) < 0.1)
			{
				/*data->map_data.dead = 1;*/
				printf("collison with player! player died\n");
				close_window(data);
			}
		}
		if (fabs(data->player_pos.x - data->map_data.sprites[i].x) < 0.1 &&
			fabs(data->player_pos.y - data->map_data.sprites[i].y) < 0.1)
		{
			/*data->map_data.dead = 1;*/
			printf("collison with player! player died\n");
			close_window(data);
		}
	}
	else
	{
		move_x = 0;
		move_y = 0;
	}
	
}

void	update_sprite(t_data *data, int i)
{
	double	move_x = 0.0;
	double	move_y = 0.0;
	double	new_x;
	double	new_y;
	double	distance;
	double	dx;
	double	dy;
	
	dx = data->player_pos.x - data->map_data.sprites[i].x;
	dy = data->player_pos.y - data->map_data.sprites[i].y;
	distance = sqrt(dx * dx + dy * dy); 
	if (distance < 4)
	{
		if (distance > 0.1)
		{
			move_x = (data->player_pos.x - data->map_data.sprites[i].x)
				/ distance * data->map_data.sprites[i].move_speed;
			move_y = (data->player_pos.y - data->map_data.sprites[i].y)
				/ distance * data->map_data.sprites[i].move_speed;
			new_x = data->map_data.sprites[i].x + move_x;
			new_y = data->map_data.sprites[i].y + move_y;
			if (new_x >= 1 && new_x < data->map_data.map_width - 1
			&& data->map_data.map[(int)data->map_data.sprites[i].y][(int)new_x] != '1')
				data->map_data.sprites[i].x = new_x;
			if (new_y >= 1 && new_y < data->map_data.map_height - 1
			&& data->map_data.map[(int)new_y][(int)data->map_data.sprites[i].x] != '1')
				data->map_data.sprites[i].y = new_y;
			if (fabs(data->player_pos.x - data->map_data.sprites[i].x) < 0.1 &&
			fabs(data->player_pos.y - data->map_data.sprites[i].y) < 0.1)
			{
				/*data->map_data.dead = 1;*/
				printf("collison with player! player died\n");
				close_window(data);
			}
		}
	}
	else
	{
		move_x = 0;
		move_y = 0;
	}
}
