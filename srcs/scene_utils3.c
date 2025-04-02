/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:50:18 by apoh              #+#    #+#             */
/*   Updated: 2025/04/02 14:50:19 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_wall_texture	*get_texture_for_ray_hit(t_data *data, t_colour *fc)
	// East wall
	// West wall
	// South wall
	// North wall
{
	if (data->map_data.map[fc->map_y][fc->map_x] == 'D')
	{
		fc->door_index = get_door_index(data, fc->map_x, fc->map_y);
		if (fc->door_index != -1 && !data->map_data.door_states[fc->door_index])
			return (&data->map_data.door_texture);
		else
			return (NULL);
	}
	else if (fc->side == 0 && fc->raydir_x > 0)
		return (&data->map_data.east_texture);
	else if (fc->side == 0 && fc->raydir_x < 0)
		return (&data->map_data.west_texture);
	else if (fc->side == 1 && fc->raydir_y > 0)
		return (&data->map_data.south_texture);
	else
		return (&data->map_data.north_texture);
}
