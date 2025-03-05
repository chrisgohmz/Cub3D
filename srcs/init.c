/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:17:41 by apoh              #+#    #+#             */
/*   Updated: 2025/03/01 18:35:29 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_data(t_data *data)
{
	data->player_pos.x = 9.5;
	data->player_pos.y = 9.5;
	data->player_direction.x = 0;
	data->player_direction.y = -1;
	data->camera_plane_pos.x = -data->player_direction.y * 0.66;
	data->camera_plane_pos.y = data->player_direction.x * 0.66;
}
