/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:17:41 by apoh              #+#    #+#             */
/*   Updated: 2025/03/06 22:12:46 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	get_player_pos_direction(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (data->map_data.map[++y])
	{
		x = -1;
		while (data->map_data.map[y][++x])
		{
			if (ft_strchr("NSEW", data->map_data.map[y][x]))
			{
				data->player_pos.x = x + 0.5;
				data->player_pos.y = y + 0.5;
				if (data->map_data.map[y][x] == 'N')
				{
					data->player_direction.x = 0;
					data->player_direction.y = -1;
				}
				else if (data->map_data.map[y][x] == 'S')
				{
					data->player_direction.x = 0;
					data->player_direction.y = 1;
				}
				else if (data->map_data.map[y][x] == 'E')
				{
					data->player_direction.x = 1;
					data->player_direction.y = 0;
				}
				else
				{
					data->player_direction.x = -1;
					data->player_direction.y = 0;
				}
				return ;
			}
		}
	}
}

void	init_data(t_data *data)
{
	get_player_pos_direction(data);
	data->camera_plane_pos.x = -data->player_direction.y * 0.66;
	data->camera_plane_pos.y = data->player_direction.x * 0.66;
}
