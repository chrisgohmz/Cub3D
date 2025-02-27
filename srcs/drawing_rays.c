/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:47:33 by apoh              #+#    #+#             */
/*   Updated: 2025/02/27 13:47:41 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	drawing_single_ray(t_data *data, t_renderdata *render)
{
	render->cos_offset = cos(render->angle_offset);
	render->sin_offset = sin(render->angle_offset);
	render->dirX = data->player_direction.x * render->cos_offset - data->player_direction.y * render->sin_offset;
	render->dirY = data->player_direction.x * render->sin_offset + data->player_direction.y * render->cos_offset;
	render->ray_end_x = render->player_screen_x + (int)(render->dirX * render->rayLength);
	render->ray_end_y = render->player_screen_y + (int)(render->dirY * render->rayLength);
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
	while (1)
	{
		if (render->current_x >= 0 && render->current_x < 1920 && render->current_y >= 0 && render->current_y < 1080)
		{
			render->pixel = (render->current_y * data->size_line) + (render->current_x *(data->bits_per_pixel / 8));
			*(unsigned int*)((char*)data->addr + render->pixel) = 0x00FF00;
		}
		if (render->current_x == render->ray_end_x && render->current_y == render->ray_end_y)
			break ;
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
}

void	drawing_multiple_rays(t_data *data, t_renderdata *render)
{
	render->num_rays = 60;
	render->rayLength = 700;
	render->fov = 3.14 / 3;
	render->k = 0;
	while (render->k < render->num_rays)
	{
		render->angle_offset = ((render->k / (double)(render->num_rays - 1)) - 0.5) * render->fov;
		render->ray_cast_angle = atan2(data->player_direction.y, data->player_direction.x) + render->angle_offset;
		cast_ray(data, render);
		render->rayLength = render->wall_distances[render->k] * 800;
		printf("Drawing ray %d: Length %2.f\n", render->k, render->rayLength);
		drawing_single_ray(data, render);
		render->k++;
	}
}
