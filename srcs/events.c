/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:32:37 by apoh              #+#    #+#             */
/*   Updated: 2025/03/07 22:53:12 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_window(t_data *data)
{
	if (data->img != NULL)
	{
		mlx_destroy_image(data->mlx, data->img);
		data->img = NULL;
	}
	if (data->win != NULL)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	if (data->mlx != NULL)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
	free(data->map_data.north_texture);
	free(data->map_data.south_texture);
	free(data->map_data.east_texture);
	free(data->map_data.west_texture);
	free_2d_arr((void ***)&data->map_data.map);
	exit(EXIT_SUCCESS);
}

int	keydown(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_window(data);
	else if (keycode == XK_Left || keycode == XK_Right)
		rotate_view(data, keycode);
	else if (keycode == XK_w || keycode == XK_s || keycode == XK_a || keycode == XK_d)
		move_player(data, keycode);
	return (1);
}
