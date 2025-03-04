/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map_cells.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:33:05 by apoh              #+#    #+#             */
/*   Updated: 2025/02/27 13:33:13 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_map_cells(t_data *data, t_renderdata *render)
{
	// this is for adding colour to each cell //
	while (render->y < 20)
	{
		render->x = 0;
		while (render->x < 20)
		{
			if (data->map[render->y][render->x] == '1')
				render->color = 0x808080;
			else
				render->color = 0x000000;
			render->i = 0;
			while (render->i < render->block_size_x)
			{
				render->j = 0;
				while (render->j < render->block_size_y)
				{
					render->pixel = ((render->y * render->block_size_y + render->j) * data->size_line) + ((render->x* render->block_size_x + render->i) * (data->bits_per_pixel / 8));
					*(unsigned int*)((char*)data->addr + render->pixel) = render->color;
					render->j++;
				}
				render->i++;
			}
			render->x++;
		}	
		render->y++;
	}
}
