/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 20:00:44 by cgoh              #+#    #+#             */
/*   Updated: 2025/03/25 22:14:59 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	redraw_image(t_data *data)
{
	struct timeval	tv;
	unsigned long	elapsed_time_in_ms;

	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img,
			&data->bits_per_pixel, &data->size_line,
			&data->endian);
	render_scene(data);
	render_map(data);
	gettimeofday(&tv, NULL);
	elapsed_time_in_ms = (tv.tv_sec - data->current_time.tv_sec) * 1000 + (tv.tv_usec - data->current_time.tv_usec) / 1000;
	if (elapsed_time_in_ms < 1000 / FRAMES_PER_SECOND)
		return ;
	data->current_time.tv_sec = tv.tv_sec;
	data->current_time.tv_usec = tv.tv_usec;
	mlx_put_image_to_window(data->mlx, data->win,
		data->img, 0, 0);
}

void	rotate_view(t_data *data, int direction)
{
	double	angle_change;
	double	oldDirX;
	double	oldPlaneX;

	angle_change = 0;
	if (direction == XK_Left)
		angle_change = -M_PI / 180;
	else if (direction == XK_Right)
		angle_change = M_PI / 180;
	oldDirX = data->player_direction.x;
	data->player_direction.x = data->player_direction.x * cos(angle_change)
	- data->player_direction.y * sin(angle_change);
	data->player_direction.y = oldDirX * sin(angle_change)
	+ data->player_direction.y * cos(angle_change);
	oldPlaneX = data->camera_plane_pos.x;
	data->camera_plane_pos.x = data->camera_plane_pos.x * cos(angle_change)
	- data->camera_plane_pos.y * sin(angle_change);
	data->camera_plane_pos.y = oldPlaneX * sin(angle_change)
	+ data->camera_plane_pos.y * cos(angle_change);
	redraw_image(data);
}

/*void	move_player(t_data *data, int direction)
{
	const double speed = 0.1;
	double new_x, new_y;

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
	{
		return;  // No movement if not a valid direction key
	}
	printf("Current position: (%f, %f)\n", data->player_pos.x, data->player_pos.y);
	printf("New position: (%f, %f)\n", new_x, new_y);
	printf("Map value at new position: %c\n", data->map[(int)new_y][(int)new_x]);
	// Check collision and update position if no collision
	if (data->map[(int)new_y][(int)new_x] != '1')
	{
		data->player_pos.x = new_x;
		data->player_pos.y = new_y;
		printf("Movement allowed\n");
		redraw_image(data);
	}
	else
	{
		printf("Movement blocked\n");
	}
}*/

static bool	can_move_to(t_data *data, double x, double y)
{
	int	map_x = (int)x;
	int	map_y = (int)y;
	char	map_cell = data->map_data.map[map_y][map_x];
	int	i;
	
	i = 0;
	if (map_cell == '1')
		return (false);
	if (map_cell == 'D')
	{
		while (i < data->map_data.num_doors)
		{
			if (data->map_data.door_x[i] == map_x && data->map_data.door_y[i] == map_y)
				return (data->map_data.door_states[i]);
			i++;
		}
		return (false);
	}
	return (true);
}


void	move_player(t_data *data, int direction)
{
	const double	speed = 0.1;
	double	new_x;
	double	new_y;
	
	if (direction == XK_w)
	{
		/*if (data->map_data.map[(int)data->player_pos.y][(int)(data->player_pos.x + data->player_direction.x * speed)] != '1')*/
		new_x = data->player_pos.x + data->player_direction.x * speed;
		/*if (data->map_data.map[(int)(data->player_pos.y + data->player_direction.y * speed)][(int)data->player_pos.x] != '1')*/
		new_y = data->player_pos.y + data->player_direction.y * speed;
	}
	else if (direction == XK_s)
	{
		/*if (data->map_data.map[(int)data->player_pos.y][(int)(data->player_pos.x - data->player_direction.x * speed)] != '1')*/
		new_x = data->player_pos.x - data->player_direction.x * speed;
		/*if (data->map_data.map[(int)(data->player_pos.y - data->player_direction.y * speed)][(int)data->player_pos.x] != '1')*/
		new_y = data->player_pos.y - data->player_direction.y * speed;
	}
	else if (direction == XK_a)
	{
		/*if (data->map_data.map[(int)data->player_pos.y][(int)(data->player_pos.x + data->player_direction.y * speed)] != '1')*/
		new_x = data->player_pos.x + data->player_direction.y * speed;
		/*if (data->map_data.map[(int)(data->player_pos.y - data->player_direction.x * speed)][(int)data->player_pos.x] != '1')*/
		new_y = data->player_pos.y - data->player_direction.x * speed;
	}
	else if (direction == XK_d)
	{
		/*if (data->map_data.map[(int)data->player_pos.y][(int)(data->player_pos.x - data->player_direction.y * speed)] != '1')*/
		new_x = data->player_pos.x - data->player_direction.y * speed;
		/*if (data->map_data.map[(int)(data->player_pos.y + data->player_direction.x * speed)][(int)data->player_pos.x] != '1')*/
		new_y = data->player_pos.y + data->player_direction.x * speed;
	}
	else
		return ;
	if (can_move_to(data, new_x, data->player_pos.y))
		data->player_pos.x = new_x;
	if (can_move_to(data, data->player_pos.x, new_y))
		data->player_pos.y = new_y;
	redraw_image(data);
}
