/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:30:28 by apoh              #+#    #+#             */
/*   Updated: 2025/03/03 21:09:50 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_map(t_data *data)
{
	t_renderdata render;
	
	ft_memset(&render, 0, sizeof(t_renderdata));
	render.block_size_x = WIDTH / 6;
	render.block_size_y = HEIGHT / 5;
	render.line_color = 0xFFFFFF;
	render.y = 0;
	// render_map_cells(data, &render);	
	// drawing_grid_lines(data, &render);	
	// drawing_player(data, &render);
	// drawing_multiple_rays(data, &render);
	render_scene(data);
}
