/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 20:00:44 by cgoh              #+#    #+#             */
/*   Updated: 2025/04/04 15:59:53 by cgoh             ###   ########.fr       */
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
	olddir_x = data->map_data.player_direction.x;
	data->map_data.player_direction.x = data->map_data.player_direction.x
		* cos(angle_change) - data->map_data.player_direction.y
		* sin(angle_change);
	data->map_data.player_direction.y = olddir_x * sin(angle_change)
		+ data->map_data.player_direction.y * cos(angle_change);
	oldplane_x = data->map_data.camera_plane_pos.x;
	data->map_data.camera_plane_pos.x = data->map_data.camera_plane_pos.x
		* cos(angle_change) - data->map_data.camera_plane_pos.y
		* sin(angle_change);
	data->map_data.camera_plane_pos.y = oldplane_x * sin(angle_change)
		+ data->map_data.camera_plane_pos.y * cos(angle_change);
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
			if (data->map_data.doors[i].x == map_x
				&& data->map_data.doors[i].y == map_y)
				return (data->map_data.doors[i].open);
			i++;
		}
		return (false);
	}
	return (true);
}

void	up_down_direction_checks_for_player(
			t_data *data, int direction, t_move *move)
{
	if (direction == XK_w)
	{
		move->x = data->map_data.player_pos.x
			+ data->map_data.player_direction.x * move->speed;
		move->y = data->map_data.player_pos.y
			+ data->map_data.player_direction.y * move->speed;
	}
	else if (direction == XK_s)
	{
		move->x = data->map_data.player_pos.x
			- data->map_data.player_direction.x * move->speed;
		move->y = data->map_data.player_pos.y
			- data->map_data.player_direction.y * move->speed;
	}
}

void	left_and_right_direction_checks_for_player(
			t_data *data, int direction, t_move *move)
{
	if (direction == XK_a)
	{
		move->x = data->map_data.player_pos.x
			+ data->map_data.player_direction.y * move->speed;
		move->y = data->map_data.player_pos.y
			- data->map_data.player_direction.x * move->speed;
	}
	else if (direction == XK_d)
	{
		move->x = data->map_data.player_pos.x
			- data->map_data.player_direction.y * move->speed;
		move->y = data->map_data.player_pos.y
			+ data->map_data.player_direction.x * move->speed;
	}
}

void	move_player(t_data *data, int direction, t_move *move)
{
	up_down_direction_checks_for_player(data, direction, move);
	left_and_right_direction_checks_for_player(data, direction, move);
	if (can_move_to(data, move->x, data->map_data.player_pos.y))
		data->map_data.player_pos.x = move->x;
	if (can_move_to(data, data->map_data.player_pos.x, move->y))
		data->map_data.player_pos.y = move->y;
}
