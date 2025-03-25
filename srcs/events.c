/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:32:37 by apoh              #+#    #+#             */
/*   Updated: 2025/03/25 22:12:22 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_window(t_data *data)
{
	int	i;
	
	i = 0;
	if (data->map_data.north_texture.img != NULL)
	{
		mlx_destroy_image(data->mlx, data->map_data.north_texture.img);
		data->map_data.north_texture.img = NULL;
	}
	if (data->map_data.south_texture.img != NULL)
	{
		mlx_destroy_image(data->mlx, data->map_data.south_texture.img);
		data->map_data.south_texture.img = NULL;
	}
	if (data->map_data.east_texture.img != NULL)
	{
		mlx_destroy_image(data->mlx, data->map_data.east_texture.img);
		data->map_data.east_texture.img = NULL;
	}
	if (data->map_data.west_texture.img != NULL)
	{
		mlx_destroy_image(data->mlx, data->map_data.west_texture.img);
		data->map_data.west_texture.img = NULL;
	}
	if (data->map_data.door_texture.img != NULL)
	{
		mlx_destroy_image(data->mlx, data->map_data.door_texture.img);
		data->map_data.door_texture.img = NULL;
	}
	if (data->map_data.sprites)
	{
		for (int i = 0; i < data->map_data.num_sprites; i++)
		{
			if (data->map_data.sprites[i].img)
				mlx_destroy_image(data->mlx, data->map_data.sprites[i].img);
		}
		free(data->map_data.sprites);
		data->map_data.sprites = NULL;
	}
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
	if (data->zBuffer)
		free(data->zBuffer);
	free(data->map_data.door_x);
	free(data->map_data.door_y);
	free(data->map_data.door_states);
	free_2d_arr((void ***)&data->map_data.map);
	exit(EXIT_SUCCESS);
}

static void	interact_with_door(t_data *data)
{
	double	min_distance = INFINITY;
	int	nearest_door_index = -1;
	int	i;
	double	dx;
	double	dy;
	double	distance;
	
	i = 0;
	// Find the nearest door
	while (i < data->map_data.num_doors)
	{
		dx = data->map_data.door_x[i] - data->player_pos.x;
		dy = data->map_data.door_y[i] - data->player_pos.y;
		distance = sqrt(dx * dx + dy * dy);
		if (distance < min_distance)
		{
			min_distance = distance;
			nearest_door_index = i;
		}
		i++;
	}
	// Toggle the state of the nearest door if it's within range
	if (nearest_door_index != -1 && min_distance < 2.0) // Adjust the range as needed
	{
		data->map_data.door_states[nearest_door_index] = !data->map_data.door_states[nearest_door_index];
		redraw_image(data); // Assuming you have a function to redraw the scene
    	}
}	

int	mouse_move(int x, int y, t_data *data)
{
	if (ft_abs(x - data->mouse_pos_x) < 100)
		return (1);
	if (x > data->mouse_pos_x)
		rotate_view(data, XK_Right);
	else if (x < data->mouse_pos_x)
		rotate_view(data, XK_Left);
	data->mouse_pos_x = x;
	data->mouse_pos_y = y;
	return (1);
}

int	keydown(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_window(data);
	else if (keycode == XK_Left || keycode == XK_Right)
		rotate_view(data, keycode);
	else if (keycode == XK_w || keycode == XK_s || keycode == XK_a || keycode == XK_d)
		move_player(data, keycode);
	else if (keycode == XK_o)
		interact_with_door(data);
	return (1);
}
