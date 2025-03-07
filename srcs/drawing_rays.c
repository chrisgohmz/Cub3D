/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:47:33 by apoh              #+#    #+#             */
/*   Updated: 2025/03/07 21:23:58 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	drawing_single_ray(t_data *data, t_renderdata *render)
{
	/*printf("dirX : %.2f\n", render->dirX);
	printf("dirY : %.2f\n", render->dirY);*/
	render->end_x = render->hitPointX * render->block_size_x;
	render->end_y = render->hitPointY * render->block_size_y;
	render->ray_end_x = (int)render->end_x;
	render->ray_end_y = (int)render->end_y;
	/*printf("ray_end_x : %d\n", render->ray_end_x);
	printf("ray_end_y : %d\n", render->ray_end_y);*/
	render->dx = abs(render->ray_end_x - render->player_screen_x);
	render->dy = abs(render->ray_end_y - render->player_screen_y);
	/*printf("dx : %d\n", render->dx);
	printf("dy : %d\n", render->dy);*/
	if (render->player_screen_x < render->ray_end_x)
		render->sx = 1;
	else
		render->sx = -1;
	if (render->player_screen_y < render->ray_end_y)
		render->sy = 1;
	else
		render->sy = -1;
	render->err = render->dx - render->dy;
	/*printf("player x %d\n", render->player_screen_x);
	printf("player y %d\n", render->player_screen_y);*/
	render->current_x = render->player_screen_x;
	render->current_y = render->player_screen_y;
	/*printf("current_x : %d\n", render->current_x);
	printf("current_y : %d\n", render->current_y);
	printf("Player world pos: (%.2f, %.2f)\n", data->player_pos.x, data->player_pos.y);
	printf("Player screen pos: (%d, %d)\n", render->player_screen_x, render->player_screen_y);
	printf("Hit point: (%.2f, %.2f)\n", render->hitPointX, render->hitPointY);
	printf("End point: (%.2f, %.2f)\n", render->end_x, render->end_y);*/

	while (1)
	{
		if (render->current_x >= 0 && render->current_x < WIDTH && render->current_y >= 0 && render->current_y < HEIGHT)
		{
			render->pixel = (render->current_y * data->size_line) + (render->current_x *(data->bits_per_pixel / 8));
			*(unsigned int*)((char*)data->addr + render->pixel) = 0x00FF00;
		}
		int map_x = render->current_x / render->block_size_x;
		int map_y = render->current_y / render->block_size_y;
		if (data->map_data.map[map_y][map_x] == '1')
			break ;
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
	render->fov = M_PI / 3;
	render->k = 0;
	while (render->k < render->num_rays)
	{
		/*printf("Player direction : (%.2f, %.2f)\n", data->player_direction.x, data->player_direction.y);*/
		/*double central_angle = atan2(data->player_direction.y, data->player_direction.x);*/
		/*printf("Central angle: %.2f radians (%.2f degrees)\n", central_angle, central_angle * 180 / 3.14);*/
		double ray_progress = (double)render->k / (render->num_rays - 1);
		render->angle_offset = (ray_progress - 0.5) * render->fov;
		/*printf("angle_offset %.2f\n", render->angle_offset);*/
		render->ray_cast_angle = atan2(data->player_direction.y, data->player_direction.x) + render->angle_offset;
		/*printf("Ray %d: offset %.2f, angle %.2f radians (%.2f degrees)\n", render->k, render->angle_offset, render->ray_cast_angle, render->ray_cast_angle * 180 / 3.14);
		printf("ray_cast_angle %.2f\n", render->ray_cast_angle);*/
		cast_ray(data, render);
		/*printf("Drawing ray %d: Angle %.2f, Distance %.2f\n", render->k, render->ray_cast_angle, render->perpWallDist);*/
		drawing_single_ray(data, render);
		render->k++;
	}
	printf("Player world pos: (%.2f, %.2f)\n", data->player_pos.x, data->player_pos.y);
	printf("Player screen pos: (%d, %d)\n", render->player_screen_x, render->player_screen_y);
}
