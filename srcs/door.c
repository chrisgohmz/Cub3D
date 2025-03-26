/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:33:26 by apoh              #+#    #+#             */
/*   Updated: 2025/03/26 14:33:37 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_door_open(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < data->map_data.num_doors)
	{
		if (data->map_data.door_x[i] == x && data->map_data.door_y[i] == y)
			return (data->map_data.door_states[i]);
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
		if (data->map_data.door_x[i] == x && data->map_data.door_y[i] == y)
			return (i);
		i++;
	}
	return (-1);
}
