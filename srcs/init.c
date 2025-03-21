/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:17:41 by apoh              #+#    #+#             */
/*   Updated: 2025/03/19 13:55:39 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_data(t_data *data)
{
	data->camera_plane_pos.x = -data->player_direction.y * 0.66;
	data->camera_plane_pos.y = data->player_direction.x * 0.66;
	data->zBuffer = malloc(sizeof(double) * WIDTH);
	if (!data->zBuffer)
	{
		perror("Failed to allocate memory for Z-buffer");
		exit(EXIT_FAILURE);
	}
}
