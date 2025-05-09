/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:43:52 by apoh              #+#    #+#             */
/*   Updated: 2025/04/11 22:32:14 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	initialising_zbuffer(t_data *data)
{
	data->x = 0;
	while (data->x < WIDTH)
	{
		data->zbuffer[data->x] = 1e30;
		data->x++;
	}
}

void	calculate_floor_and_ceiling_data(t_colour *fc, t_data *data)
{
	fc->raydir_x0 = data->map_data.player_direction.x
		- data->map_data.camera_plane_pos.x;
	fc->raydir_y0 = data->map_data.player_direction.y
		- data->map_data.camera_plane_pos.y;
	fc->raydir_x1 = data->map_data.player_direction.x
		+ data->map_data.camera_plane_pos.x;
	fc->raydir_y1 = data->map_data.player_direction.y
		+ data->map_data.camera_plane_pos.y;
	fc->p = data->y - HEIGHT / 2;
	fc->pos_z = 0.5 * HEIGHT;
	fc->rowdistance = fc->pos_z / fc->p;
	fc->floorstep_x = fc->rowdistance * (fc->raydir_x1 - fc->raydir_x0) / WIDTH;
	fc->floorstep_y = fc->rowdistance * (fc->raydir_y1 - fc->raydir_y0) / WIDTH;
	fc->floor_x = data->map_data.player_pos.x + fc->rowdistance * fc->raydir_x0;
	fc->floor_y = data->map_data.player_pos.y + fc->rowdistance * fc->raydir_y0;
}

void	apply_colour_to_floor_and_ceiling(t_colour *fc, t_data *data)
{
	data->y = -1;
	while (++data->y < HEIGHT)
	{
		calculate_floor_and_ceiling_data(fc, data);
		data->x = -1;
		while (++data->x < WIDTH)
		{
			fc->floor_x += fc->floorstep_x;
			fc->floor_y += fc->floorstep_y;
			if (data->x > MINIMAP_SIZE || data->y > MINIMAP_SIZE)
				ft_mlx_pixel_put(data, data->x, data->y,
					data->map_data.floor_colour);
			if (data->x > MINIMAP_SIZE || HEIGHT - data->y - 1 > MINIMAP_SIZE)
				ft_mlx_pixel_put(data, data->x,
					HEIGHT - data->y - 1, data->map_data.ceiling_colour);
		}
	}
}
