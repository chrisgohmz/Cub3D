/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:44:24 by apoh              #+#    #+#             */
/*   Updated: 2025/04/03 18:31:13 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calculate_texture_data(t_colour *fc, t_data *data)
{
	fc->camera_x = 2 * data->x / (double)WIDTH - 1;
	fc->raydir_x = data->map_data.player_direction.x + data->map_data.camera_plane_pos.x
		* fc->camera_x;
	fc->raydir_y = data->map_data.player_direction.y + data->map_data.camera_plane_pos.y
		* fc->camera_x;
	fc->map_x = (int)data->map_data.player_pos.x;
	fc->map_y = (int)data->map_data.player_pos.y;
	fc->hit = 0;
	if (!fc->raydir_x)
		fc->deltadist_x = 1e30;
	else
		fc->deltadist_x = fabs(1 / fc->raydir_x);
	if (!fc->raydir_y)
		fc->deltadist_y = 1e30;
	else
		fc->deltadist_y = fabs(1 / fc->raydir_y);
}

void	initialising_data_for_raycasting(t_colour *fc, t_data *data)
{
	if (fc->raydir_x < 0)
	{
		fc->step_x = -1;
		fc->sidedist_x = (data->map_data.player_pos.x - fc->map_x)
			* fc->deltadist_x;
	}
	else
	{
		fc->step_x = 1;
		fc->sidedist_x = (fc->map_x + 1.0 - data->map_data.player_pos.x)
			* fc->deltadist_x;
	}
	if (fc->raydir_y < 0)
	{
		fc->step_y = -1;
		fc->sidedist_y = (data->map_data.player_pos.y - fc->map_y)
			* fc->deltadist_y;
	}
	else
	{
		fc->step_y = 1;
		fc->sidedist_y = (fc->map_y + 1.0 - data->map_data.player_pos.y)
			* fc->deltadist_y;
	}
}

void	raycast_walls_and_doors(t_colour *fc, t_data *data)
{
	while (!fc->hit)
	{
		if (fc->sidedist_x < fc->sidedist_y)
		{
			fc->sidedist_x += fc->deltadist_x;
			fc->map_x += fc->step_x;
			fc->side = 0;
		}
		else
		{
			fc->sidedist_y += fc->deltadist_y;
			fc->map_y += fc->step_y;
			fc->side = 1;
		}
		if (data->map_data.map[fc->map_y][fc->map_x] == '1')
			fc->hit = 1;
		else if (data->map_data.map[fc->map_y][fc->map_x] == 'D')
		{
			fc->door_index = get_door_index(data, fc->map_x, fc->map_y);
			if (fc->door_index != -1
				&& !data->map_data.doors[fc->door_index].open)
				fc->hit = 1;
		}
	}
}

void	calculate_3d_rendering_data(t_colour *fc, t_data *data)
{
	if (fc->side == 0)
		fc->perpwalldist = fc->sidedist_x - fc->deltadist_x;
	else
		fc->perpwalldist = fc->sidedist_y - fc->deltadist_y;
	fc->lineheight = (int)(HEIGHT / fc->perpwalldist);
	fc->y1 = -fc->lineheight / 2 + HEIGHT / 2;
	if (fc->y1 < 0)
		fc->y1 = 0;
	fc->y2 = fc->lineheight / 2 + HEIGHT / 2;
	if (fc->y2 >= HEIGHT)
		fc->y2 = HEIGHT - 1;
	printf("Wall Column %d: Height=%d\n", data->x, fc->lineheight);
}

void	get_texture_coordinates_and_colour(
			t_colour *fc, t_data *data, t_img_data *img_data)
	// Get fractional part of wallX
	// Flip texture horizontally
{
	if (fc->side == 0)
		fc->wall_x = data->map_data.player_pos.y + fc->perpwalldist * fc->raydir_y;
	else
		fc->wall_x = data->map_data.player_pos.x + fc->perpwalldist * fc->raydir_x;
	fc->wall_x -= floor(fc->wall_x);
	fc->tex_x = (int)(fc->wall_x * img_data->width);
	if ((fc->side == 0 && fc->raydir_x < 0)
		|| (fc->side == 1 && fc->raydir_y > 0))
		fc->tex_x = img_data->width - fc->tex_x - 1;
	fc->tex_y = (fc->y1 - HEIGHT / 2 + fc->lineheight / 2)
		* img_data->height / fc->lineheight;
	fc->color = *(unsigned int *)(img_data->addr + fc->tex_y
			* img_data->size_line + fc->tex_x * (img_data->bits_per_pixel / 8));
	if (data->x > MINIMAP_SIZE || fc->y1 > MINIMAP_SIZE)
		ft_mlx_pixel_put(data, data->x, fc->y1, fc->color);
	fc->y1++;
}
