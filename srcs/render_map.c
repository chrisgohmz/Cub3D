/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:30:28 by apoh              #+#    #+#             */
/*   Updated: 2025/03/07 22:58:08 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_map(t_data *data)
{
	t_renderdata	render;

	ft_memset(&render, 0, sizeof(t_renderdata));
	if (data->map_data.map_width > data->map_data.map_height)
	{
		render.block_size_x = MINIMAP_SIZE / data->map_data.map_width;
		render.block_size_y = MINIMAP_SIZE / data->map_data.map_width;
	}
	else
	{
		render.block_size_x = MINIMAP_SIZE / data->map_data.map_height;
		render.block_size_y = MINIMAP_SIZE / data->map_data.map_height;
	}
	render.line_color = 0xFFFFFF;
	render.y = 0;
	render_map_cells(data, &render);
	drawing_grid_lines(data, &render);
	drawing_player(data, &render);
	drawing_multiple_rays(data, &render);
	render_scene(data);
	render_sprites(data);
}
