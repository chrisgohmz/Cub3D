/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:47:33 by apoh              #+#    #+#             */
/*   Updated: 2025/04/11 22:31:55 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	setting_up_data_to_start_drawing_line(t_renderdata *render)
	// converting end point by getting its pixel coordinates //
	// converting end point to int coordinates //
	// as graphics usually requires int //
	// calculating distance from ray to player //
	// determine which direction ray should move //
	// depending on player and ray position //
{
	render->end_x = render->hitpoint_x * render->block_size_x;
	render->end_y = render->hitpoint_y * render->block_size_y;
	render->ray_end_x = (int)render->end_x;
	render->ray_end_y = (int)render->end_y;
	render->dx = abs(render->ray_end_x - render->player_screen_x);
	render->dy = abs(render->ray_end_y - render->player_screen_y);
	if (render->player_screen_x < render->ray_end_x)
		render->sx = 1;
	else
		render->sx = -1;
	if (render->player_screen_y < render->ray_end_y)
		render->sy = 1;
	else
		render->sy = -1;
	render->err = render->dx - render->dy;
	render->current_x = render->player_screen_x;
	render->current_y = render->player_screen_y;
}

void	draw_ray_if_within_screen(t_data *data, t_renderdata *render)
{
	if (render->current_x >= 0 && render->current_x < WIDTH
		&& render->current_y >= 0 && render->current_y < HEIGHT)
	{
		render->pixel = (render->current_y * data->size_line)
			+ (render->current_x *(data->bits_per_pixel / 8));
		*(unsigned int *)((char *)data->addr + render->pixel)
			= 0x00FF00;
	}
}

void	implementing_bresenham_algo(t_renderdata *render)
	// determine whether to move in x direction or y direction //
{
	render->e2 = 2 * render->err;
	if (render->e2 > -render->dy)
	{
		render->err = render->err - render->dy;
		render->current_x = render->current_x + render->sx;
	}
	if (render->e2 < render->dx)
	{
		render->err = render->err + render->dx;
		render->current_y = render->current_y + render->sy;
	}
}

void	drawing_single_ray(t_data *data, t_renderdata *render)

{
	int	map_x;
	int	map_y;

	setting_up_data_to_start_drawing_line(render);
	while (1)
	{
		draw_ray_if_within_screen(data, render);
		map_x = render->current_x / render->block_size_x;
		map_y = render->current_y / render->block_size_y;
		if (map_x < 0 || map_x >= data->map_data.map_width
			|| map_y < 0 || map_y >= data->map_data.map_height)
			break ;
		if (data->map_data.map[map_y][map_x] == '1')
			break ;
		if (render->current_x == render->ray_end_x
			&& render->current_y == render->ray_end_y)
			break ;
		implementing_bresenham_algo(render);
	}
}

void	drawing_multiple_rays(t_data *data, t_renderdata *render)
{
	double	ray_progress;

	render->num_rays = WIDTH;
	render->fov = M_PI / 180 * 66;
	render->k = 0;
	while (render->k < render->num_rays)
	{
		ray_progress = (double)render->k / (render->num_rays - 1);
		render->angle_offset = (ray_progress - 0.5) * render->fov;
		render->ray_cast_angle = atan2(data->map_data.player_direction.y,
				data->map_data.player_direction.x) + render->angle_offset;
		cast_ray(data, render);
		drawing_single_ray(data, render);
		render->k++;
	}
}
