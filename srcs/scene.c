/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:22:38 by cgoh              #+#    #+#             */
/*   Updated: 2025/03/28 16:52:54 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_scene(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		data->zBuffer[x] = 1e30;
		x++;
	}
	y = -1;
	while (++y < HEIGHT)
	{
		float rayDirX0 = data->player_direction.x - data->camera_plane_pos.x;
		float rayDirY0 = data->player_direction.y - data->camera_plane_pos.y;
		float rayDirX1 = data->player_direction.x + data->camera_plane_pos.x;
		float rayDirY1 = data->player_direction.y + data->camera_plane_pos.y;

		int p = y - HEIGHT / 2;
		float posZ = 0.5 * HEIGHT;
		float rowDistance = posZ / p;
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / WIDTH;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / WIDTH;
		float floorX = data->player_pos.x + rowDistance * rayDirX0;
		float floorY = data->player_pos.y + rowDistance * rayDirY0;
		x = -1;
		while (++x < WIDTH)
		{	
			floorX += floorStepX;
			floorY += floorStepY;
			if (x > MINIMAP_SIZE || y > MINIMAP_SIZE)
				ft_mlx_pixel_put(data, x, y, data->map_data.floor_colour);
			if (x > MINIMAP_SIZE || HEIGHT - y - 1 > MINIMAP_SIZE)
				ft_mlx_pixel_put(data, x, HEIGHT - y - 1, data->map_data.ceiling_colour);
		}
	}
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
			if (data->map_data.map[mapY][mapX] == '1')
				hit = 1;
			else if (data->map_data.map[mapY][mapX] == 'D')
			{
				int	door_index = get_door_index(data, mapX, mapY);
				if (door_index != -1 && !data->map_data.door_states[door_index])
					hit = 1;
			}
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
			t_wall_texture *texture;
			if (data->map_data.map[mapY][mapX] == 'D')
			{
				int	door_index = get_door_index(data, mapX, mapY);
				if (door_index != -1 && !data->map_data.door_states[door_index])
					texture = &data->map_data.door_texture;
				else
					continue ;
			}
			else if (side == 0 && rayDirX > 0)
				texture = &data->map_data.east_texture; // East wall
			else if (side == 0 && rayDirX < 0)
				texture = &data->map_data.west_texture; // West wall
			else if (side == 1 && rayDirY > 0)
				texture = &data->map_data.south_texture; // South wall
			else
				texture = &data->map_data.north_texture; // North wall
			// Calculate texture coordinates
			double wallX; 
			if (side == 0)
				wallX = data->player_pos.y + perpWallDist * rayDirY;
			else
				wallX = data->player_pos.x + perpWallDist * rayDirX;
			wallX -= floor(wallX); // Get fractional part of wallX
			int texX = (int)(wallX * texture->img_width);
			if ((side == 0 && rayDirX < 0) || (side == 1 && rayDirY > 0))
				texX = texture->img_width - texX - 1; // Flip texture horizontally
			int texY = (y1 - HEIGHT / 2 + lineHeight / 2) * texture->img_height / lineHeight;
			// Fetch color from texture
			int color = *(unsigned int *)(texture->addr + texY * texture->size_line + texX * (texture->bits_per_pixel / 8));
			if (x > MINIMAP_SIZE || y1 > MINIMAP_SIZE)
				ft_mlx_pixel_put(data, x, y1, color);
			y1++;
		}
		data->zBuffer[x] = perpWallDist;
	}
}
