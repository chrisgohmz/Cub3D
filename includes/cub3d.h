/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:50:23 by cgoh              #+#    #+#             */
/*   Updated: 2025/02/24 21:24:55 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../mlx-linux/mlx.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;
	char	map[5][6];
	int	bits_per_pixel;
	int	size_line;
	int	endian;
	t_point	player_pos;
	t_point	player_direction;
	t_point	camera_plane_pos;
}	t_data;

typedef struct s_renderdata
{
	double	cos_offset;
	double	sin_offset;
	double	dirX;
	double	dirY;
	double	rayLength;
	double	angle_offset;
	double	fov;
	int	x;
	int	y;
	int	block_size_x;
	int	block_size_y;
	int	color;
	int	line_color;
	int	i;
	int	j;
	int	pixel;
	int	player_screen_x;
	int	player_screen_y;
	int	player_radius;
	int	player_color;
	int	py;
	int	px;
	int	ray_end_x;
	int	ray_end_y;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
	int	current_x;
	int	current_y;
	int	num_rays;
	int	k;
}	t_renderdata;

// init.c //
void	init_data(t_data *data);

// close_window.c //
int	close_window(t_data *data);

// print_map.c //
void	print_map(t_data *data);

// render_map.c //
void	render_map(t_data *data);

// render_map_cells.c //
void	render_map_cells(t_data *data, t_renderdata *render);

// drawing_grid_lines.c //
void	drawing_grid_lines(t_data *data, t_renderdata *render);

// drawing_player.c //
void	drawing_player(t_data *data, t_renderdata *render);

// drawing_rays.c //
void	drawing_single_ray(t_data *data, t_renderdata *render);
void	drawing_multiple_rays(t_data *data, t_renderdata *render);


#endif
