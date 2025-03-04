/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 20:00:44 by cgoh              #+#    #+#             */
/*   Updated: 2025/03/01 20:19:11 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	redraw_image(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img,
			&data->bits_per_pixel, &data->size_line,
			&data->endian);
	/*render_scene(data);*/
	render_map(data);
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

void	move_player(t_data *data, int direction)
{
	const double	speed = 0.1;
	
	if (direction == XK_w)
	{
		if (data->map[(int)(data->player_pos.x + data->player_direction.x * speed)][(int)data->player_pos.y] == '0')
			data->player_pos.x += data->player_direction.x * speed;
		if (data->map[(int)data->player_pos.x][(int)(data->player_pos.y + data->player_direction.y * speed)] == '0')
			data->player_pos.y += data->player_direction.y * speed;
	}
	else if (direction == XK_s)
	{
		if (data->map[(int)(data->player_pos.x - data->player_direction.x * speed)][(int)data->player_pos.y] == '0')
			data->player_pos.x -= data->player_direction.x * speed;
		if (data->map[(int)data->player_pos.x][(int)(data->player_pos.y - data->player_direction.y * speed)] == '0')
			data->player_pos.y -= data->player_direction.y * speed;
	}
	else if (direction == XK_a)
	{
		if (data->map[(int)(data->player_pos.x + data->player_direction.x * speed)][(int)data->player_pos.y] == '0')
			data->player_pos.x += data->player_direction.x * speed;
		if (data->map[(int)data->player_pos.x][(int)(data->player_pos.y - data->player_direction.y * speed)] == '0')
			data->player_pos.y -= data->player_direction.y * speed;
	}
	else if (direction == XK_d)
	{
		if (data->map[(int)(data->player_pos.x - data->player_direction.x * speed)][(int)data->player_pos.y] == '0')
			data->player_pos.x -= data->player_direction.x * speed;
		if (data->map[(int)data->player_pos.x][(int)(data->player_pos.y + data->player_direction.y * speed)] == '0')
			data->player_pos.y += data->player_direction.y * speed;
	}
	redraw_image(data);
}
