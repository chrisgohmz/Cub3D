/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:50:23 by cgoh              #+#    #+#             */
/*   Updated: 2025/03/31 20:01:46 by cgoh             ###   ########.fr       */
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
# include <sys/time.h>
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

typedef struct s_move
{
	double	speed;
	double	x;
	double	y;
}	t_move;

typedef struct s_colour
{
	float	raydir_x0;
	float	raydir_y0;
	float	raydir_x1;
	float	raydir_y1;
	float	pos_z;
	float	rowdistance;
	float	floorstep_x;
	float	floorstep_y;
	float	floor_x;
	float	floor_y;
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	perpwalldist;
	double	wall_x;
	int		p;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		door_index;
	int		lineheight;
	int		y1;
	int		y2;
	int		tex_x;
	int		tex_y;
	int		color;
}	t_colour;

typedef struct s_game
{
	int	i;
	int	new_x;
	int	new_y;
	int	old_x;
	int	old_y;
}	t_game;

typedef struct s_sprite_update
{
	double	move_x;
	double	move_y;
	double	new_x;
	double	new_y;
	double	distance;
	double	dx;
	double	dy;
}	t_sprite_update;

typedef struct s_render_sprites
{
	double	sprite_x;
	double	sprite_y;
	double	invdet;
	double	transform_x;
	double	transform_y;
	int		i;
	int		spritescreen_x;
	int		spriteheight;
	int		drawstart_y;
	int		drawend_y;
	int		spritewidth;
	int		drawstart_x;
	int		drawend_x;
	int		stripe;
	int		y_loop;
	int		d;
	int		tex_x;
	int		tex_y;
	int		color;
}	t_render_sprites;

typedef struct s_sprite
{
	double	x;
	double	y;
	double	move_speed;
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	original_cell;
}	t_sprite;

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

typedef struct s_mapdata
{
	t_wall_texture	north_texture;
	t_wall_texture	south_texture;
	t_wall_texture	west_texture;
	t_wall_texture	east_texture;
	t_wall_texture	door_texture;
	t_sprite		*sprites;
	t_sprite		head_sprites[13];
	char			**map;
	char			**elements;
	char			**elements_info;
	char			*line;
	char			*file_content;
	char			*tmp;
	bool			dead;
	bool			*door_states;
	int				num_sprites;
	int				head_sprite_index;
	int				num_doors;
	int				*door_x;
	int				*door_y;
	int				floor_colour;
	int				ceiling_colour;
	int				map_height;
	int				map_width;
	int				fd;
}	t_mapdata;

typedef struct s_data
{
	struct timeval	current_time;
	void			*mlx;
	void			*win;
	void			*img;
	void			*addr;
	t_point			player_pos;
	t_point			player_direction;
	t_point			camera_plane_pos;
	t_mapdata		map_data;
	double			*zbuffer;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				mouse_pos_x;
	int				mouse_pos_y;
	int				i;
	int				x;
	int				y;
}	t_data;

typedef struct s_renderdata
{
	double	perpwalldist;
	double	cos_offset;
	double	sin_offset;
	double	dir_x;
	double	dir_y;
	double	hitpoint_x;
	double	hitpoint_y;
	double	deltadist_x;
	double	deltadist_y;
	double	angle_offset;
	double	ray_cast_angle;
	double	fov;
	double	end_x;
	double	end_y;
	int		map_x;
	int		map_y;
	int		x;
	int		y;
	int		block_size_x;
	int		block_size_y;
	int		color;
	int		line_color;
	int		i;
	int		j;
	int		pixel;
	int		player_screen_x;
	int		player_screen_y;
	int		player_radius;
	int		player_color;
	int		py;
	int		px;
	int		ray_end_x;
	int		ray_end_y;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
	int		current_x;
	int		current_y;
	int		num_rays;
	int		k;
}	t_renderdata;

typedef struct s_raycast
{
	double	sidedist_x;
	double	sidedist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_raycast;

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color);

// scene.c //
void	render_scene(t_data *data);

// scene_utils1.c //
void	initialising_zbuffer(t_data *data);
void	calculating_data_for_floor_and_ceiling(t_colour *fc, t_data *data);
void	apply_colour_to_floor_and_ceiling(t_colour *fc, t_data *data);

// scene_utils2.c //
void	calculating_data_for_textures(t_colour *fc, t_data *data);
void	initialising_data_for_raycasting(t_colour *fc, t_data *data);
void	applying_raycasting_on_walls_and_doors(t_colour *fc, t_data *data);
void	calculating_data_for_3d_image(t_colour *fc);
void	count_texture_coordinates_and_fetch_colour(
			t_colour *fc, t_data *data, t_wall_texture *texture);

// scene_utils3.c //
t_wall_texture	*get_texture_for_ray_hit(t_data *data, t_colour *fc);

// events.c //
void	interact_with_door(t_data *data);
int		mouse_move(int x, int y, t_data *data);
int		keydown(int keycode, t_data *data);

// image.c //
void	rotate_view(t_data *data, int direction);
bool	can_move_to(t_data *data, double x, double y);
void	move_player(t_data *data, int direction, t_move *move);

// drawing_rays.c //
void	drawing_single_ray(t_data *data, t_renderdata *render);
void	drawing_multiple_rays(t_data *data, t_renderdata *render);
void	interact_with_door(t_data *data);

// ray_casting.c //
void	cast_ray(t_data *data, t_renderdata *render);

// parsing.c //
bool	get_map(t_data *data);
int		parsing(t_data *data, char *file_path);

// parsing_utils1.c //
bool	found_map_start(const char *str);
int		count_arr_elements(char **arr);
bool	print_error(const char *message);
bool	check_color_range(int *color, char *color_str);
int		count_commas(const char *str);

// parsing_utils2.c //
int		validating_commas(char *str);
int		validating_array_elements(char **color_rgb_arr);
int		get_color(char *str);
bool	get_texture(t_wall_texture *wall, t_data *data, char *path);
bool	load_door_texture(t_data *data);

// parsing_utils3.c //
bool	load_sprite_texture(t_sprite *sprite, t_data *data, char *path);
bool	check_for_nsew_textures(t_data *data);
bool	check_for_fc_textures(t_data *data);

// parsing_utils4.c //
bool	get_element_info(t_data *data);
bool	check_wall_surround(t_mapdata *map_data, char **map_copy, int x, int y);
bool	check_map_valid(t_data *data);
void	setting_up_player_direction(t_data *data, int x, int y);
void	get_player_pos_direction(t_data *data);

// pasring_utils5.c //
bool	check_map_chars_valid(const char *line, bool *player_found);
bool	get_map(t_data *data);

// init.c //
void	init_data(t_data *data);

// render_map.c //
void	render_map(t_data *data);

// render_map_cells.c //
void	render_map_cells(t_data *data, t_renderdata *render);

// drawing_grid_lines.c //
void	drawing_grid_lines(t_data *data, t_renderdata *render);

// drawing_player.c //
void	drawing_player(t_data *data, t_renderdata *render);

// door.c //
int		is_door_open(t_data *data, int x, int y);
int		get_door_index(t_data *data, int x, int y);

// free.c //
void	free_textures(t_data *data);
void	freeing_sprites(t_data *data);
void	free_others(t_data *data);
int		close_window(t_data *data);

// sprite.c //
void	sort_sprites(t_data *data);
void	render_sprites(t_data *data);

// sprite_utils1.c //
void	updating_enemy_status(t_sprite_update *update, t_data *data, int i);
void	update_sprite(t_data *data, int i);
void	update_sprite_time(t_data *data, struct timeval new_time);
void	draw_sprites(t_data *data);
void	render_head_sprites(t_data *data);

// sprite_utils2.c //
void	calculate_relative_position_and_transformations(
			t_render_sprites *sprites, t_data *data);
void	calculate_screen_position_and_size_of_sprite(t_render_sprites *sprites);
int		validate_texture_coordinates(t_render_sprites *sprites, t_data *data);
void	calculating_texture_y_coordinates(
			t_render_sprites *sprites, t_data *data);
void	get_color_for_texture(t_render_sprites *sprites, t_data *data);

// sprite_utils3.c //
void	calculating_texture_x_coordinates(
			t_render_sprites *sprites, t_data *data);
int		checking_for_transform_y_value(t_render_sprites *sprites);
int		process_sprite(t_render_sprites *sprites, t_data *data);
int		validate_stripes(t_render_sprites *sprites, t_data *data);
void	render_pixels(t_render_sprites *sprites, t_data *data);

#endif
