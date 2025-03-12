/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:50:23 by cgoh              #+#    #+#             */
/*   Updated: 2025/03/10 19:34:51 by cgoh             ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <X11/keysym.h>
# include <stdbool.h>
# define WIDTH 1920
# define HEIGHT 1080
# define MINIMAP_SIZE 400
# define ON_KEYDOWN 2
# define ON_MOUSEDOWN 4
# define ON_MOUSEMOVE 6
# define ON_DESTROY 17
# define NORTH "NO"
# define SOUTH "SO"
# define WEST "WE"
# define EAST "EA"
# define FLOOR "F"
# define CEILING "C"

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_wall_texture
{
	void	*img;
	char	*addr;
	int		img_width;
	int		img_height;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_wall_texture;

typedef struct	s_mapdata
{
	t_wall_texture	north_texture;
	t_wall_texture	south_texture;
	t_wall_texture	west_texture;
	t_wall_texture	east_texture;
	t_wall_texture	door_texture;
	int		door_x;
	int		door_y;
	int		floor_colour;
	int		ceiling_colour;
	char	**map;
	int		map_height;
	int		map_width;
	int		fd;
	char	*line;
	char	*file_content;
	char	*tmp;
	char	**elements;
	char	**elements_info;
}	t_mapdata;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	t_point		player_pos;
	t_point		player_direction;
	t_point		camera_plane_pos;
	t_mapdata	map_data;
}	t_data;

typedef struct s_renderdata
{
	double	perpWallDist;
	double	cos_offset;
	double	sin_offset;
	double	dirX;
	double	dirY;
	double	hitPointX;
	double	hitPointY;
	double	deltaDistX;
	double	deltaDistY;
	double	angle_offset;
	double	ray_cast_angle;
	double	fov;
	int	mapX;
	int	mapY;
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
	double	end_x;
	double	end_y;
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

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color);
void	render_scene(t_data *data);
void	rotate_view(t_data *data, int direction);
int		keydown(int keycode, t_data *data);
void	move_player(t_data *data, int direction);

// init.c //
void	init_data(t_data *data);

// close_window.c //
int	close_window(t_data *data);

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

// ray_casting.c //
void	cast_ray(t_data *data, t_renderdata *render);

// parsing.c //
int		parsing(t_data *data, char *file_path);

#endif
