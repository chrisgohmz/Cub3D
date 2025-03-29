/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:09:41 by apoh              #+#    #+#             */
/*   Updated: 2025/03/29 20:06:24 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	sort_sprites(t_data *data)
{
	int	i;
	int	j;
	t_sprite	temp;
	double	dist_i;
	double	dist_j;
	
	i = 0;
	while (i < data->map_data.num_sprites - 1)
	{
		j = i + 1;
        	while (j < data->map_data.num_sprites)
        	{
        		dist_i = pow(data->player_pos.x - data->map_data.sprites[i].x, 2) +
        		pow(data->player_pos.y - data->map_data.sprites[i].y, 2);
        		dist_j = pow(data->player_pos.x - data->map_data.sprites[j].x, 2) +
        		pow(data->player_pos.y - data->map_data.sprites[j].y, 2);
        		if (dist_i < dist_j) // Sort descending by distance
        		{
        			temp = data->map_data.sprites[i];
        			data->map_data.sprites[i] = data->map_data.sprites[j];
        			data->map_data.sprites[j] = temp;
        		}
        		j++;
        	}
        	i++;
        }
}

void	render_sprites(t_data *data)
{
	int	i;
	double	spriteX;
	double	spriteY;
	double	invDet;
	double	transformX;
	double	transformY;
	int	spriteScreenX;
	int	spriteHeight;
	int	drawStartY;
	int	drawEndY;
	int	spriteWidth;
	int	drawStartX;
	int	drawEndX;
	int	stripe;
	int	y_loop;
	int	d;
	int	texX;
	int	texY;
	int	color;
	
	i = 0;
	sort_sprites(data);
	while (i < data->map_data.num_sprites)
	{
		spriteX = data->map_data.sprites[i].x - data->player_pos.x;
		spriteY = data->map_data.sprites[i].y - data->player_pos.y;
		invDet = 1.0 / (data->camera_plane_pos.x * data->player_direction.y - data->player_direction.x * data->camera_plane_pos.y);
		transformX = invDet * (data->player_direction.y * spriteX - data->player_direction.x * spriteY);
		transformY = invDet * (-data->camera_plane_pos.y * spriteX + data->camera_plane_pos.x * spriteY);
		spriteScreenX = (int)((WIDTH / 2) * (1 + transformX / transformY));
		spriteHeight = abs((int)(HEIGHT / (transformY)));
		spriteWidth = abs((int)(HEIGHT / transformY));
		drawStartY = -spriteHeight / 2 + HEIGHT / 2;
		if (drawStartY < 0)
			drawStartY = 0;
		drawEndY = spriteHeight / 2 + HEIGHT / 2;
		if (drawEndY >= HEIGHT)
			drawEndY = HEIGHT - 1;
		drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= WIDTH)
			drawEndX = WIDTH - 1;
		stripe = drawStartX;
		while (stripe < drawEndX)
		{
			texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * data->map_data.sprites[i].width / spriteWidth) / 256;
			
			if (transformY > 0 && stripe > 0 && stripe < WIDTH && transformY < data->zBuffer[stripe])
			{
				y_loop = drawStartY;
				while (y_loop < drawEndY)
				{
					d = (y_loop) * 256 - HEIGHT * 128 + spriteHeight * 128;
					texY = ((d * data->map_data.sprites[i].height) / spriteHeight) / 256;
					if (texY < 0)
						texY = 0;
					else if (texY >= data->map_data.sprites[i].height)
						texY = data->map_data.sprites[i].height - 1;
					color = *(unsigned int *)(data->map_data.sprites[i].addr + texY * data->map_data.sprites[i].size_line + texX * data->map_data.sprites[i].bits_per_pixel / 8);
					if ((color & 0x00FFFFFF) != 0 && (stripe > MINIMAP_SIZE || y_loop > MINIMAP_SIZE))
						ft_mlx_pixel_put(data, stripe, y_loop, color);
					y_loop++;
				}
			}
			stripe++;
		}
		i++;
	}
}

void	update_sprite(t_data *data, int i)
{
	double	move_x = 0.0;
	double	move_y = 0.0;
	double	new_x;
	double	new_y;
	double	distance;
	double	dx;
	double	dy;
	
	dx = data->player_pos.x - data->map_data.sprites[i].x;
	dy = data->player_pos.y - data->map_data.sprites[i].y;
	distance = sqrt(dx * dx + dy * dy);
	if (distance > 4)
	{
		move_x = 0.0;
		move_y = 0.0;
	}
	else
	{
		move_x = (data->player_pos.x - data->map_data.sprites[i].x) / distance * data->map_data.sprites[i].move_speed;
		move_y = (data->player_pos.y - data->map_data.sprites[i].y) / distance * data->map_data.sprites[i].move_speed;
	}
	new_x = data->map_data.sprites[i].x + move_x;
	new_y = data->map_data.sprites[i].y + move_y;
	if (new_x >= 1 && new_x < data->map_data.map_width - 1 && data->map_data.map[(int)data->map_data.sprites[i].y][(int)new_x] != '1')
		data->map_data.sprites[i].x = new_x;
	if (new_y >= 1 && new_y < data->map_data.map_height - 1 && data->map_data.map[(int)new_y][(int)data->map_data.sprites[i].x] != '1')
        data->map_data.sprites[i].y = new_y;
    if (fabs(data->player_pos.x - data->map_data.sprites[i].x) < 0.1 &&
			fabs(data->player_pos.y - data->map_data.sprites[i].y) < 0.1)
	{
		data->map_data.dead = 1;
		//close_window(data);
	}
}
