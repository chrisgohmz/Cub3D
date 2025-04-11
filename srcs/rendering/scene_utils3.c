/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:50:18 by apoh              #+#    #+#             */
/*   Updated: 2025/04/11 22:32:20 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	get_wall_img_data(t_img_data *img_data, t_wall_texture *wall)
{
	img_data->img = wall->img;
	img_data->addr = wall->addr;
	img_data->width = wall->img_width;
	img_data->height = wall->img_height;
	img_data->bits_per_pixel = wall->bits_per_pixel;
	img_data->size_line = wall->size_line;
	img_data->endian = wall->endian;
}

static void	get_door_img_data(t_data *data, t_colour *fc, t_img_data *img_data)
{
	img_data->img = data->map_data.doors[fc->door_index].img;
	img_data->addr = data->map_data.doors[fc->door_index].addr;
	img_data->width = data->map_data.doors[fc->door_index].width;
	img_data->height = data->map_data.doors[fc->door_index].height;
	img_data->bits_per_pixel
		= data->map_data.doors[fc->door_index].bits_per_pixel;
	img_data->size_line = data->map_data.doors[fc->door_index].size_line;
	img_data->endian = data->map_data.doors[fc->door_index].endian;
}

void	get_img_data_for_ray_hit(
			t_data *data, t_colour *fc, t_img_data *img_data)
{
	if (data->map_data.map[fc->map_y][fc->map_x] == 'D')
	{
		fc->door_index = get_door_index(data, fc->map_x, fc->map_y);
		if (fc->door_index != -1 && !data->map_data.doors[fc->door_index].open)
			get_door_img_data(data, fc, img_data);
		else
			return ;
	}
	else if (fc->side == 0 && fc->raydir_x > 0)
		get_wall_img_data(img_data, &data->map_data.east_texture);
	else if (fc->side == 0 && fc->raydir_x < 0)
		get_wall_img_data(img_data, &data->map_data.west_texture);
	else if (fc->side == 1 && fc->raydir_y > 0)
		get_wall_img_data(img_data, &data->map_data.south_texture);
	else
		get_wall_img_data(img_data, &data->map_data.north_texture);
}
