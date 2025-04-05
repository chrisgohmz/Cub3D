/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:22:38 by cgoh              #+#    #+#             */
/*   Updated: 2025/03/28 16:52:54 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_scene(t_data *data)
{
	t_img_data	img_data;
	t_colour		fc;

	ft_memset(&fc, 0, sizeof(t_colour));
	initialising_zbuffer(data);
	apply_colour_to_floor_and_ceiling(&fc, data);
	data->x = -1;
	while (++data->x < WIDTH)
	{
		calculate_texture_data(&fc, data);
		initialising_data_for_raycasting(&fc, data);
		raycast_walls_and_doors(&fc, data);
		calculate_3d_rendering_data(&fc, data);
		while (fc.y1 <= fc.y2)
		{
			get_img_data_for_ray_hit(data, &fc, &img_data);
			if (!img_data.img)
				continue ;
			get_texture_coordinates_and_colour(&fc, data, &img_data);
		}
		data->zbuffer[data->x] = fc.perpwalldist;
	}
}
