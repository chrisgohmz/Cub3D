/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 20:00:44 by cgoh              #+#    #+#             */
/*   Updated: 2025/03/01 20:19:11 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	redraw_image(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img,
			&data->bits_per_pixel, &data->size_line,
			&data->endian);
	render_scene(data);
	mlx_put_image_to_window(data->mlx, data->win,
		data->img, 0, 0);
}

void	rotate_view(t_data *data, int direction)
{
	double	angle_change;

	if (direction == XK_Left)
		angle_change = M_PI / 180;
	else if (direction == XK_Right)
		angle_change = -M_PI / 180;
	data->player_direction.x = data->player_direction.x * cos(angle_change)
	- data->player_direction.y * sin(angle_change);
	data->player_direction.y = data->player_direction.x * sin(angle_change)
	+ data->player_direction.y * cos(angle_change);
	redraw_image(data);
}
