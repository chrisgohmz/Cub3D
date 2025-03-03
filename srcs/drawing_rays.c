/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:47:33 by apoh              #+#    #+#             */
/*   Updated: 2025/02/27 19:04:30 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	drawing_single_ray(t_data *data, t_renderdata *render)
{
	int	scale = 630;
	
	printf("dirX : %.2f\n", render->dirX);
	printf("dirY : %.2f\n", render->dirY);
	render->end_x = render->player_screen_x + (render->dirX * render->wall_distances[render->k] * scale);
	render->end_y = render->player_screen_y + (render->dirY * render->wall_distances[render->k] * scale);
	render->ray_end_x = (int)(render->end_x);
	render->ray_end_y = (int)(render->end_y);
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
	render->fov = 3.14 / 3;
	render->k = 0;
	while (render->k < render->num_rays)
	{
		render->angle_offset = ((render->k / (double)(render->num_rays - 1)) - 0.5) * render->fov;
		printf("angle_offset %.2f\n", render->angle_offset);
		render->ray_cast_angle = atan2(data->player_direction.y, data->player_direction.x) + render->angle_offset;
		printf("ray_cast_angle %.2f\n", render->ray_cast_angle);
		cast_ray(data, render);
		printf("Drawing ray %d: Angle %.2f, Distance %.2f\n", render->k, render->ray_cast_angle, render->wall_distances[render->k]);
		drawing_single_ray(data, render);
		render->k++;
	}
}
