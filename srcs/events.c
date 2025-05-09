/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:32:37 by apoh              #+#    #+#             */
/*   Updated: 2025/04/04 16:28:54 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	interact_with_door(t_data *data)
{
	bool	doors_changed;
	int		i;

	i = 0;
	doors_changed = false;
	while (i < data->map_data.num_doors)
	{
		data->map_data.doors[i].open = !data->map_data.doors[i].open;
		doors_changed = true;
		i++;
	}
}

int	mouse_move(int x, int y, t_data *data)
{
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
	t_move	move;

	ft_memset(&move, 0, sizeof(t_move));
	move.speed = 0.1;
	if (keycode == XK_Escape)
		close_window(data);
	else if (keycode == XK_Left || keycode == XK_Right)
		rotate_view(data, keycode);
	else if (keycode == XK_w || keycode == XK_s
		|| keycode == XK_a || keycode == XK_d)
		move_player(data, keycode, &move);
	else if (keycode == XK_o)
		interact_with_door(data);
	return (1);
}
