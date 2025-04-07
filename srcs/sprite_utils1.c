/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:36:14 by apoh              #+#    #+#             */
/*   Updated: 2025/04/07 20:51:33 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	update_enemy_position_and_status(
			t_sprite_update *update, t_data *data, int i)
{
	update->move_x = (data->map_data.player_pos.x - data->map_data.sprites[i].x)
		/ update->distance * data->map_data.sprites[i].move_speed;
	update->move_y = (data->map_data.player_pos.y - data->map_data.sprites[i].y)
		/ update->distance * data->map_data.sprites[i].move_speed;
	update->new_x = data->map_data.sprites[i].x + update->move_x;
	update->new_y = data->map_data.sprites[i].y + update->move_y;
	if (update->new_x >= 1 && update->new_x < data->map_data.map_width - 1
		&& data->map_data.map[(int)data->map_data.sprites[i].y]
		[(int)update->new_x] != '1')
		data->map_data.sprites[i].x = update->new_x;
	if (update->new_y >= 1 && update->new_y < data->map_data.map_height - 1
		&& data->map_data.map[(int)update->new_y]
		[(int)data->map_data.sprites[i].x] != '1')
		data->map_data.sprites[i].y = update->new_y;
	if (fabs(data->map_data.player_pos.x - data->map_data.sprites[i].x) < 1
		&& fabs(data->map_data.player_pos.y - data->map_data.sprites[i].y) < 1)
		data->map_data.dead = 1;
}

void	update_sprite(t_data *data, int i)
{
	t_sprite_update	update;

	ft_memset(&update, 0, sizeof(t_sprite_update));
	update.dx = data->map_data.player_pos.x - data->map_data.sprites[i].x;
	update.dy = data->map_data.player_pos.y - data->map_data.sprites[i].y;
	update.distance = sqrt(update.dx * update.dx + update.dy * update.dy);
	if (update.distance < 4)
	{
		if (update.distance > 0.1)
			update_enemy_position_and_status(&update, data, i);
	}
	else
	{
		update.move_x = 0.0;
		update.move_y = 0.0;
	}
}

void	update_sprite_time(t_data *data, struct timeval new_time)
{
	data->current_time.tv_sec = new_time.tv_sec;
	data->current_time.tv_usec = new_time.tv_usec;
	data->map_data.head_sprite_index++;
}

void	draw_sprites(t_data *data)
{
	int	color;
	int	x;
	int	y;

	y = -1;
	while (++y < data->map_data.head_sprites[0].height)
	{
		x = -1;
		while (++x < data->map_data.head_sprites[0].width)
		{
			color = *(unsigned int *)(data->map_data.head_sprites
				[data->map_data.head_sprite_index].addr + y
					* data->map_data.head_sprites
				[data->map_data.head_sprite_index].size_line
					+ x * data->map_data.head_sprites
				[data->map_data.head_sprite_index].bits_per_pixel / 8);
			ft_mlx_pixel_put(data, x, y, color);
		}
	}
}

void	render_head_sprites(t_data *data)
{
	struct timeval	new_time;
	unsigned long	time_elapsed_in_ms;

	if (data->map_data.dead)
	{
		gettimeofday(&new_time, NULL);
		time_elapsed_in_ms = (new_time.tv_sec - data->current_time.tv_sec)
			* 1000 + (new_time.tv_usec - data->current_time.tv_usec) / 1000;
		if (time_elapsed_in_ms >= 20)
			update_sprite_time(data, new_time);
		if (data->map_data.head_sprite_index == 13)
			close_window(data);
		draw_sprites(data);
	}
}
