/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chris_test_rays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:22:38 by cgoh              #+#    #+#             */
/*   Updated: 2025/03/01 20:06:17 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_scene(t_data *data)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		double cameraX = 2 * x / (double)WIDTH - 1;
		double rayDirX = data->player_direction.x + data->camera_plane_pos.x * cameraX;
		double rayDirY = data->player_direction.y + data->camera_plane_pos.y * cameraX;
		int mapX = (int)data->player_pos.x;
		int mapY = (int)data->player_pos.y;
		double	sideDistX;
		double	sideDistY;
		double	deltaDistX;
		double	deltaDistY;
		double	perpWallDist;
		int		stepX;
		int		stepY;
		int		hit = 0;
		int		side;

		if (!rayDirX)
			deltaDistX = 1e30;
		else
			deltaDistX = fabs(1 / rayDirX);
		if (!rayDirY)
			deltaDistY = 1e30;
		else
			deltaDistY = fabs(1 / rayDirY);
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (data->player_pos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->player_pos.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (data->player_pos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->player_pos.y) * deltaDistY;
		}
		while (!hit)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			hit = (data->map[mapX][mapY] == '1');
		}
		if (side == 0)
			perpWallDist = sideDistX - deltaDistX;
		else
			perpWallDist = sideDistY - deltaDistY;
		int	lineHeight = (int)(HEIGHT / perpWallDist);
		int	y1 = -lineHeight / 2 + HEIGHT / 2;
		if (y1 < 0)
			y1 = 0;
		int	y2 = lineHeight / 2 + HEIGHT / 2;
		if (y2 >= HEIGHT)
			y2 = HEIGHT - 1;
		while (y1 <= y2)
		{
			ft_mlx_pixel_put(data, x, y1, 0xFF0000);
			y1++;
		}
	}
}
