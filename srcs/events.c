/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:32:37 by apoh              #+#    #+#             */
/*   Updated: 2025/03/26 19:11:43 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	interact_with_door(t_data *data)
	// Find the nearest door //
	// Toggle the state of the nearest door if it's within range //
	// Adjust the range as needed //
{
	data->map_data.i = 0;
	data->map_data.nearest_door_index = -1;
	data->map_data.min_distance = INFINITY;
	while (data->map_data.i < data->map_data.num_doors)
	{
		data->map_data.dx = data->map_data.door_x[data->map_data.i]
			- data->player_pos.x;
		data->map_data.dy = data->map_data.door_y[data->map_data.i]
			- data->player_pos.y;
		data->map_data.distance = sqrt(data->map_data.dx * data->map_data.dx
				+ data->map_data.dy * data->map_data.dy);
		if (data->map_data.distance <= data->map_data.min_distance)
		{
			if (data->map_data.distance < data->map_data.min_distance || data->map_data.nearest_door_index == -1)
			{
				data->map_data.min_distance = data->map_data.distance;
				data->map_data.nearest_door_index = data->map_data.i;
			}
		}
		data->map_data.i++;
	}
	if (data->map_data.nearest_door_index != -1
		&& data->map_data.min_distance < 200)
	{
		data->map_data.door_states[data->map_data.nearest_door_index]
			= !data->map_data.door_states[data->map_data.nearest_door_index];
	}
}

int	mouse_move(int x, int y, t_data *data)
{
	if (x > data->mouse_pos_x)
		rotate_view(data, XK_Right);
	else if (x < data->mouse_pos_x)
		rotate_view(data, XK_Left);
	data->mouse_pos_x = x;
	data->mouse_pos_y = y;
	return (1);
}

int	keydown(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_window(data);
	else if (keycode == XK_Left || keycode == XK_Right)
		rotate_view(data, keycode);
	else if (keycode == XK_w || keycode == XK_s
		|| keycode == XK_a || keycode == XK_d)
		move_player(data, keycode);
	else if (keycode == XK_o)
		interact_with_door(data);
	return (1);
}
