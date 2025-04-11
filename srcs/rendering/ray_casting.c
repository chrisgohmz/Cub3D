/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:07:05 by apoh              #+#    #+#             */
/*   Updated: 2025/04/11 22:32:01 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calculate_step_and_initial_side_dist(t_data *data,
			t_renderdata *render, t_raycast *ray)
		// Calculate step and initial sideDist //
{
	if (render->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (data->map_data.player_pos.x - render->map_x)
			* render->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (render->map_x + 1.0 - data->map_data.player_pos.x)
			* render->deltadist_x;
	}
	if (render->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (data->map_data.player_pos.y - render->map_y)
			* render->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (render->map_y + 1.0 - data->map_data.player_pos.y)
			* render->deltadist_y;
	}
}

void	detecting_ray_collisons(t_data *data,
			t_renderdata *render, t_raycast *ray)
	// first checks if its out of bounds // 
	// second checks if its hitting objects //
{
	if (render->map_x < 0 || render->map_x >= MINIMAP_SIZE
		* render->block_size_x || render->map_y < 0
		|| render->map_y >= MINIMAP_SIZE * render->block_size_y)
	{
		ray->hit = 1;
		render->hitpoint_x = render->map_x;
		render->hitpoint_y = render->map_y;
	}
	if ((data->map_data.map[(int)render->map_y][(int)render->map_x] == '1') ||
	(data->map_data.map[(int)render->map_y][(int)render->map_x] == 'D'
	&& !is_door_open(data, (int)render->map_x, (int)render->map_y)) ||
	(data->map_data.map[(int)render->map_y][(int)render->map_x] == 'M'))
		ray->hit = 1;
}

void	performing_dda(t_data *data, t_renderdata *render, t_raycast *ray)
	// Perform DDA //
{
	while (ray->hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x = ray->sidedist_x + render->deltadist_x;
			render->map_x = render->map_x + ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y = ray->sidedist_y + render->deltadist_y;
			render->map_y = render->map_y + ray->step_y;
			ray->side = 1;
		}
		detecting_ray_collisons(data, render, ray);
	}
}

void	calculate_distance_projected_on_camera(t_data *data,
			t_renderdata *render, t_raycast *ray)
	// Calculate distance projected on camera direction //
	// (avoiding fisheye effect) //
{
	if (ray->side == 0)
	{
		render->perpwalldist = (render->map_x - data->map_data.player_pos.x
				+ (1 - ray->step_x) / 2) / render->dir_x;
		render->hitpoint_x = render->map_x + (1 - ray->step_x) / 2.0;
		render->hitpoint_y = data->map_data.player_pos.y + render->perpwalldist
			* render->dir_y;
	}
	else
	{
		render->perpwalldist = (render->map_y - data->map_data.player_pos.y
				+ (1 - ray->step_y) / 2) / render->dir_y;
		render->hitpoint_x = data->map_data.player_pos.x + render->perpwalldist
			* render->dir_x;
		render->hitpoint_y = render->map_y + (1 - ray->step_y) / 2.0;
	}
}

void	cast_ray(t_data *data, t_renderdata *render)
	// dirX = where it is moving in the x-axis //
	// dirY = where it is moving in the y-axis //
	// mapX = converting it back to map coordinates //
	// instead of floating points //
	// mapY = converting it back to map coordinates //
	// instead of floating points //
	// deltaDist X = how far ray moves per unit of x //
	// moved when it hit next vertical line //
	// deltaDist Y = how far ray moves per unit of y //
	// moved when it hit next horizontal line //
{
	t_raycast	ray;

	render->dir_x = cos(render->ray_cast_angle);
	render->dir_y = sin(render->ray_cast_angle);
	render->map_x = (int)data->map_data.player_pos.x;
	render->map_y = (int)data->map_data.player_pos.y;
	render->deltadist_x = fabs(1 / render->dir_x);
	render->deltadist_y = fabs(1 / render->dir_y);
	ray.hit = 0;
	calculate_step_and_initial_side_dist(data, render, &ray);
	performing_dda(data, render, &ray);
	calculate_distance_projected_on_camera(data, render, &ray);
}
