/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:30:28 by apoh              #+#    #+#             */
/*   Updated: 2025/03/29 22:07:31 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*static void	render_head_sprites(t_data *data)
{
	int	color;
	int	x;
	int	y;
	struct timeval	new_time;
	unsigned long	time_elapsed_in_ms;
	
	if (data->map_data.dead)
	{
		gettimeofday(&new_time, NULL);
		time_elapsed_in_ms = (new_time.tv_sec - data->current_time.tv_sec) * 1000 + (new_time.tv_usec - data->current_time.tv_usec) / 1000;
		if (time_elapsed_in_ms < 100)
			return ;
		y = -1;
		while (++y < HEIGHT)
		{
			x = -1;
			while (++x < WIDTH)
			{
				color = *(unsigned int *)(data->map_data.head_sprites[data->map_data.head_sprite_index].addr + y * data->map_data.head_sprites[data->map_data.head_sprite_index].size_line + x * data->map_data.head_sprites[data->map_data.head_sprite_index].bits_per_pixel / 8);
				if (color & 0xFFFFFF)
					ft_mlx_pixel_put(data, x, y, color);
			}
		}
		if (data->map_data.head_sprite_index == 11)
			close_window(data);
		data->map_data.head_sprite_index++;
		data->current_time.tv_sec = new_time.tv_sec;
		data->current_time.tv_usec = new_time.tv_usec;
	}
}*/

void	render_map(t_data *data)
{
	t_renderdata	render;

	/*if (!data->map_data.dead)*/
	ft_memset(&render, 0, sizeof(t_renderdata));
	if (data->map_data.map_width > data->map_data.map_height)
	{
		render.block_size_x = MINIMAP_SIZE / data->map_data.map_width;
		render.block_size_y = MINIMAP_SIZE / data->map_data.map_width;
	}
	else
	{
		render.block_size_x = MINIMAP_SIZE / data->map_data.map_height;
		render.block_size_y = MINIMAP_SIZE / data->map_data.map_height;
	}
	render.line_color = 0xFFFFFF;
	render.y = 0;
	render_map_cells(data, &render);
	drawing_grid_lines(data, &render);
	drawing_player(data, &render);
	drawing_multiple_rays(data, &render);
	render_scene(data);
	render_sprites(data);
	/*else
		render_head_sprites(data);*/
}
