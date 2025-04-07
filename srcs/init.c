/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:17:41 by apoh              #+#    #+#             */
/*   Updated: 2025/04/03 18:27:19 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_data(t_data *data)
{
	data->map_data.camera_plane_pos.x = -data->map_data.player_direction.y
		* 0.66;
	data->map_data.camera_plane_pos.y = data->map_data.player_direction.x
		* 0.66;
	data->zbuffer = malloc(sizeof(double) * WIDTH);
	if (!data->zbuffer)
		close_window(data);
}
