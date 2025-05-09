/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:43:32 by apoh              #+#    #+#             */
/*   Updated: 2025/04/11 22:31:50 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	drawing_player(t_data *data, t_renderdata *render)
	// this is for drawing a dot for the player coordinates, //
	// but shifting it to the middle of the cell for realistic purposes //
{
	render->player_screen_x = data->map_data.player_pos.x
		* render->block_size_x;
	render->player_screen_y = data->map_data.player_pos.y
		* render->block_size_y;
	render->player_radius = 2;
	render->player_color = 0xFF0000;
	render->py = -render->player_radius;
	while (render->py <= render->player_radius)
	{
		render->px = -render->player_radius;
		while (render->px <= render->player_radius)
		{
			if (render->px * render->px + render->py * render->py
				<= render->player_radius * render->player_radius)
			{
				render->pixel = ((render->player_screen_y + render->py)
						* data->size_line) + ((render->player_screen_x
							+ render->px) * (data->bits_per_pixel / 8));
				*(unsigned int *)((char *)data->addr + render->pixel)
					= render->player_color;
			}
			render->px++;
		}
		render->py++;
	}
}
