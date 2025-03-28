/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 20:00:44 by cgoh              #+#    #+#             */
/*   Updated: 2025/03/26 19:09:40 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_view(t_data *data, int direction)
{
	double	angle_change;
	double	olddir_x;
	double	oldplane_x;

	angle_change = 0;
	if (direction == XK_Left)
		angle_change = -M_PI / 180;
	else if (direction == XK_Right)
		angle_change = M_PI / 180;
	olddir_x = data->player_direction.x;
	data->player_direction.x = data->player_direction.x * cos(angle_change)
		- data->player_direction.y * sin(angle_change);
	data->player_direction.y = olddir_x * sin(angle_change)
		+ data->player_direction.y * cos(angle_change);
	oldplane_x = data->camera_plane_pos.x;
	data->camera_plane_pos.x = data->camera_plane_pos.x * cos(angle_change)
		- data->camera_plane_pos.y * sin(angle_change);
	data->camera_plane_pos.y = oldplane_x * sin(angle_change)
		+ data->camera_plane_pos.y * cos(angle_change);
}

bool	can_move_to(t_data *data, double x, double y)
{
	char	map_cell;
	int		map_x;
	int		map_y;
	int		i;

	i = 0;
	map_x = (int)x;
	map_y = (int)y;
	map_cell = data->map_data.map[map_y][map_x];
	if (map_cell == '1')
		return (false);
	if (map_cell == 'D')
	{
		while (i < data->map_data.num_doors)
		{
			if (data->map_data.door_x[i] == map_x
				&& data->map_data.door_y[i] == map_y)
				return (data->map_data.door_states[i]);
			i++;
		}
		return (false);
	}
	return (true);
}

void	move_player(t_data *data, int direction)
{
	const double	speed;
	double			new_x;
	double			new_y;

	speed = 0.1;
	if (direction == XK_w)
	{
		new_x = data->player_pos.x + data->player_direction.x * speed;
		new_y = data->player_pos.y + data->player_direction.y * speed;
	}
	else if (direction == XK_s)
	{
		new_x = data->player_pos.x - data->player_direction.x * speed;
		new_y = data->player_pos.y - data->player_direction.y * speed;
	}
	else if (direction == XK_a)
	{
		new_x = data->player_pos.x + data->player_direction.y * speed;
		new_y = data->player_pos.y - data->player_direction.x * speed;
	}
	else if (direction == XK_d)
	{
		new_x = data->player_pos.x - data->player_direction.y * speed;
		new_y = data->player_pos.y + data->player_direction.x * speed;
	}
	else
		return ;
	if (can_move_to(data, new_x, data->player_pos.y))
		data->player_pos.x = new_x;
	if (can_move_to(data, data->player_pos.x, new_y))
		data->player_pos.y = new_y;
}
