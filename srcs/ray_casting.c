/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:07:05 by apoh              #+#    #+#             */
/*   Updated: 2025/02/27 17:07:28 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cast_ray(t_data *data, t_renderdata *render)
{
	double	sideDistX;
	double	sideDistY;
	int	stepX;
	int	stepY;
	int	hit;
	int	side; // 0 for X side, 1 for Y side

	render->dirX = cos(render->ray_cast_angle);
	render->dirY = sin(render->ray_cast_angle);
	render->mapX = (int)data->player_pos.x;
	render->mapY = (int)data->player_pos.y;
	render->deltaDistX = fabs(1 / render->dirX);
	render->deltaDistY = fabs(1 / render->dirY);
	hit = 0;
	/*printf("dirX :%.2f\n", render->dirX);
	printf("dirY :%.2f\n", render->dirY);
	printf("mapX :%d\n", render->mapX);
	printf("mapY : %d\n", render->mapY);
	printf("deltaDistX :%.2f\n", render->deltaDistX);
	printf("deltaDistY :%.2f\n", render->deltaDistY);*/
	// Calculate step and initial sideDist
	if (render->dirX < 0)
	{
		stepX = -1;
		sideDistX = (data->player_pos.x - render->mapX) * render->deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (render->mapX + 1.0 - data->player_pos.x) * render->deltaDistX;
	}
	if (render->dirY < 0)
	{
		stepY = -1;
		sideDistY = (data->player_pos.y - render->mapY) * render->deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (render->mapY + 1.0 - data->player_pos.y) * render->deltaDistY;
	}
	// Perform DDA
	while (hit == 0)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX = sideDistX + render->deltaDistX;
			render->mapX = render->mapX + stepX;
			side = 0;
		}
		else
		{
			sideDistY = sideDistY + render->deltaDistY;
			render->mapY = render->mapY + stepY;
			side = 1;
		}
		if (render->mapX < 0 || render->mapX >= 20 || render->mapY < 0 || render->mapY >= 20)
		{
			hit = 1;
			render->hitPointX = render->mapX;
			render->hitPointY = render->mapY;
		}
		if (data->map[(int)render->mapY][(int)render->mapX] == '1')
		{
			/*printf("Wall collison detected\n");*/
			hit = 1;
		}
	}
	// Calculate distance projected on camera direction (avoiding fisheye effect)
	if (side == 0)
	{
		render->perpWallDist = (render->mapX - data->player_pos.x + (1 - stepX) / 2) / render->dirX;	
		render->hitPointX = render->mapX + (1 - stepX) / 2.0;
		render->hitPointY = data->player_pos.y + render->perpWallDist * render->dirY;
	}
	else
	{
		render->perpWallDist = (render->mapY - data->player_pos.y + (1 - stepY) / 2) / render->dirY;
		render->hitPointX = data->player_pos.x + render->perpWallDist * render->dirX;
		render->hitPointY = render->mapY + (1 - stepY) / 2.0;
	}
	/*printf("Ray %d: Angle %.2f, Distance %.2f\n", render->k, render->ray_cast_angle, render->perpWallDist);
	printf("Ray hit at: (%.2f, %.2f)\n", render->hitPointX, render->hitPointY);*/
}
