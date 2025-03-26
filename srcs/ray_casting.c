/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:07:05 by apoh              #+#    #+#             */
/*   Updated: 2025/03/06 21:11:20 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	calculate_step_and_initial_side_dist(t_data *data,
			t_renderdata *render, t_raycast *ray)
		// Calculate step and initial sideDist //
{
	if (render->dirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (data->player_pos.x - render->mapX)
			* render->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (render->mapX + 1.0 - data->player_pos.x)
			* render->deltaDistX;
	}
	if (render->dirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (data->player_pos.y - render->mapY)
			* render->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (render->mapY + 1.0 - data->player_pos.y)
			* render->deltaDistY;
	}
}

static void	further_condition_checks(t_data *data,
			t_renderdata *render, t_raycast *ray)
	// first checks if its out of bounds // 
	// second checks if its hitting objects //
{
	if (render->mapX < 0 || render->mapX >= MINIMAP_SIZE
		* render->block_size_x || render->mapY < 0
		|| render->mapY >= MINIMAP_SIZE * render->block_size_y)
	{
		ray->hit = 1;
		render->hitPointX = render->mapX;
		render->hitPointY = render->mapY;
	}
	if ((data->map_data.map[(int)render->mapY][(int)render->mapX] == '1') ||
	(data->map_data.map[(int)render->mapY][(int)render->mapX] == 'D'
	&& !is_door_open(data, (int)render->mapX, (int)render->mapY)) ||
	(data->map_data.map[(int)render->mapY][(int)render->mapX] == 'M'))
		ray->hit = 1;
}

static void	performing_dda(t_data *data, t_renderdata *render, t_raycast *ray)
	// Perform DDA //
{
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX = ray->sideDistX + render->deltaDistX;
			render->mapX = render->mapX + ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY = ray->sideDistY + render->deltaDistY;
			render->mapY = render->mapY + ray->stepY;
			ray->side = 1;
		}
		further_condition_checks(data, render, ray);
	}
}

static void	calculate_distance_projected_on_camera(t_data *data,
			t_renderdata *render, t_raycast *ray)
	// Calculate distance projected on camera direction //
	// (avoiding fisheye effect) //
{
	if (ray->side == 0)
	{
		render->perpWallDist = (render->mapX - data->player_pos.x
				+ (1 - ray->stepX) / 2) / render->dirX;
		render->hitPointX = render->mapX + (1 - ray->stepX) / 2.0;
		render->hitPointY = data->player_pos.y + render->perpWallDist
			* render->dirY;
	}
	else
	{
		render->perpWallDist = (render->mapY - data->player_pos.y
				+ (1 - ray->stepY) / 2) / render->dirY;
		render->hitPointX = data->player_pos.x + render->perpWallDist
			* render->dirX;
		render->hitPointY = render->mapY + (1 - ray->stepY) / 2.0;
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

	render->dirX = cos(render->ray_cast_angle);
	render->dirY = sin(render->ray_cast_angle);
	render->mapX = (int)data->player_pos.x;
	render->mapY = (int)data->player_pos.y;
	render->deltaDistX = fabs(1 / render->dirX);
	render->deltaDistY = fabs(1 / render->dirY);
	ray.hit = 0;
	calculate_step_and_initial_side_dist(data, render, &ray);
	performing_dda(data, render, &ray);
	calculate_distance_projected_on_camera(data, render, &ray);
}
