/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:39:37 by apoh              #+#    #+#             */
/*   Updated: 2025/02/27 13:39:50 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	drawing_grid_lines(t_data *data, t_renderdata *render)
{
	// this is for drawing lines for each cell //
	render->y = 0;
	while (render->y <= 20)
	{
		render->i = 0;
		while (render->i < 20 * render->block_size_x)
		{
			render->pixel = (render->y * render->block_size_y * data->size_line) + (render->i * (data->bits_per_pixel / 8));
			*(unsigned int*)((char*)data->addr + render->pixel) = render->line_color;
			render->i++;
		}
		render->y++;
	}
	render->x = 0;
	while (render->x <= 20)
	{
		render->j = 0;
		while (render->j < 20 * render->block_size_y)
		{
			render->pixel = (render->j * data->size_line) + (render->x * render->block_size_x  * (data->bits_per_pixel / 8));
			*(unsigned int*)((char*)data->addr + render->pixel) = render->line_color;
			render->j++;
		}
		render->x++;
	}
}
