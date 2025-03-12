/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map_cells.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:33:05 by apoh              #+#    #+#             */
/*   Updated: 2025/03/07 21:15:04 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_map_cells(t_data *data, t_renderdata *render)
{
	// this is for adding colour to each cell //
	while (render->y < data->map_data.map_height)
	{
		render->x = 0;
		while (render->x < data->map_data.map_width && data->map_data.map[render->y][render->x])
		{
			if (data->map_data.map[render->y][render->x] == '1')
				render->color = 0x808080;
			else if (data->map_data.map[render->y][render->x] == 'D')
				render->color = 0xFF0000;
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
