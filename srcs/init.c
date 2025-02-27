/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:17:41 by apoh              #+#    #+#             */
/*   Updated: 2025/02/27 12:17:53 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_data(t_data *data)
{
	data->player_pos.x = 3;
	data->player_pos.y = 3;
	data->player_direction.x = 0;
	data->player_direction.y = -1;
	data->camera_plane_pos.x = 0;
	data->camera_plane_pos.y = 0.66;
}
