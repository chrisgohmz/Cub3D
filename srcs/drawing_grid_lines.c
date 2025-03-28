/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_grid_lines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:39:37 by apoh              #+#    #+#             */
/*   Updated: 2025/03/06 21:51:38 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static	void	drawing_lines_for_height(t_data *data, t_renderdata *render)
{
	render->y = 0;
	while (render->y <= data->map_data.map_height)
	{
		render->i = 0;
		while (render->i < data->map_data.map_width * render->block_size_x)
		{
			if (render->y < data->map_data.map_height
				&& (size_t)(render->i / render->block_size_x)
			< ft_strlen(data->map_data.map[render->y])
				&& data->map_data.map[render->y]
					[render->i / render->block_size_x] != ' ')
			{
				render->pixel = (render->y * render->block_size_y
						* data->size_line) + (render->i
						* (data->bits_per_pixel / 8));
				*(unsigned int *)((char *)data->addr + render->pixel)
					= render->line_color;
			}
			render->i++;
		}
		render->y++;
	}
}

static void	drawing_lines_for_width(t_data *data, t_renderdata *render)
{
	render->x = 0;
	while (render->x <= data->map_data.map_width)
	{
		render->j = 0;
		while (render->j < data->map_data.map_height * render->block_size_y)
		{
			if ((size_t)render->x <= ft_strlen(data->map_data.map
					[render->j / render->block_size_y])
				&& data->map_data.map[render->j / render->block_size_y]
				[render->x] != ' ')
			{
				render->pixel = (render->j * data->size_line)
					+ (render->x * render->block_size_x
						* (data->bits_per_pixel / 8));
				*(unsigned int *)((char *)data->addr + render->pixel)
					= render->line_color;
			}
			render->j++;
		}
		render->x++;
	}
}

void	drawing_grid_lines(t_data *data, t_renderdata *render)
	// this is for drawing lines for each cell //
{
	drawing_lines_for_height(data, render);
	drawing_lines_for_width(data, render);
}
