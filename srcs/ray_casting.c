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

int	wall_collision(t_data *data, double x, double y)
{
	int	map_x;
	int	map_y;
	
	map_x = (int)x;
	map_y = (int)y;
	
	if (map_x < 0 || map_x >= 6 || map_y < 0 || map_y >= 5)
		return (1);
	if (data->map[map_y][map_x] == '1')
		return (1);
	return (0);
}

void	cast_ray(t_data *data, t_renderdata *render)
{
	double	ray_x = data->player_pos.x;
	double	ray_y = data->player_pos.y;
	double	ray_dir_x = cos(render->ray_cast_angle);
	double	ray_dir_y = sin(render->ray_cast_angle);
	double	step = 0.1;
	double	distance = 0;
	
	while (distance <= 10)
	{
		if (wall_collision(data, ray_x, ray_y) == 1)
			break ;
		ray_x = ray_x + (ray_dir_x * step);
		ray_y = ray_y + (ray_dir_y * step);
		distance = distance + step;
	}
	render->wall_distances[render->k] = distance;
	printf("Ray %d: Angle %.2f, Distance %.2f\n", render->k, render->ray_cast_angle, distance);
}
