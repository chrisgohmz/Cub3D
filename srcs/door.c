/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:33:26 by apoh              #+#    #+#             */
/*   Updated: 2025/04/04 16:02:02 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_door_open(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < data->map_data.num_doors)
	{
		if (data->map_data.doors[i].x == x && data->map_data.doors[i].y == y)
			return (data->map_data.doors[i].open);
		i++;
	}
	return (0);
}

int	get_door_index(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < data->map_data.num_doors)
	{
		if (data->map_data.doors[i].x == x && data->map_data.doors[i].y == y)
			return (i);
		i++;
	}
	return (-1);
}
