/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:50:23 by cgoh              #+#    #+#             */
/*   Updated: 2025/04/05 17:29:12 by cgoh             ###   ########.fr       */
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

typedef	struct s_img_data
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_img_data;

typedef struct s_sprite
{
	double	x;
	double	y;
	double	original_x;
	double	original_y;
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

typedef struct s_door
{
	int		x;
	int		y;
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	bool	open;
}	t_door;

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
	t_door			*doors;
	t_sprite		*sprites;
	t_sprite		head_sprites[13];
	char			**map;
	int				map_width;
	int				map_height;
	bool			dead;
	int				num_sprites;
	int				head_sprite_index;
	int				num_doors;
	int				floor_colour;
	int				ceiling_colour;
	t_point			player_pos;
	t_point			player_direction;
	t_point			camera_plane_pos;
}	t_mapdata;

typedef struct s_data
{
	struct timeval	current_time;
	void			*mlx;
	void			*win;
	void			*img;
	void			*addr;
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

typedef struct s_readmap
{
	bool	player_found;
	int		fd;
}	t_readmap;

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color);

// scene.c //
void	render_scene(t_data *data);

// scene_utils1.c //
void	initialising_zbuffer(t_data *data);
void	calculate_floor_and_ceiling_data(t_colour *fc, t_data *data);
void	apply_colour_to_floor_and_ceiling(t_colour *fc, t_data *data);

// scene_utils2.c //
void	calculate_texture_data(t_colour *fc, t_data *data);
void	initialising_data_for_raycasting(t_colour *fc, t_data *data);
void	raycast_walls_and_doors(t_colour *fc, t_data *data);
void	calculate_3d_rendering_data(t_colour *fc);
void	get_texture_coordinates_and_colour(
	t_colour *fc, t_data *data, t_img_data *img_data);

// scene_utils3.c //
void	get_img_data_for_ray_hit(t_data *data, t_colour *fc,
	t_img_data *img_data);

// events.c //
void	interact_with_door(t_data *data);
int		mouse_move(int x, int y, t_data *data);
int		keydown(int keycode, t_data *data);

// image.c //
void	rotate_view(t_data *data, int direction);
bool	can_move_to(t_data *data, double x, double y);
void	move_player(t_data *data, int direction, t_move *move);

// drawing_rays.c //
void	setting_up_data_to_start_drawing_line(t_renderdata *render);
void	draw_ray_if_within_screen(t_data *data, t_renderdata *render);
void	implementing_bresenham_algo(t_renderdata *render);
void	drawing_single_ray(t_data *data, t_renderdata *render);
void	drawing_multiple_rays(t_data *data, t_renderdata *render);

// ray_casting.c //
void	calculate_step_and_initial_side_dist(t_data *data,
			t_renderdata *render, t_raycast *ray);
void	detecting_ray_collisons(t_data *data,
			t_renderdata *render, t_raycast *ray);
void	performing_dda(t_data *data, t_renderdata *render, t_raycast *ray);
void	calculate_distance_projected_on_camera(t_data *data,
			t_renderdata *render, t_raycast *ray);
void	cast_ray(t_data *data, t_renderdata *render);

// parsing.c //
bool	get_map(t_data *data, char **line, char **file_content, int fd);
int		parsing(t_data *data, char *file_path);
bool	split_elements_and_extract_info(t_mapdata *map_data,
	char **file_content, void *mlx);

// parsing_utils1.c //
int		count_arr_elements(char **arr);
bool	print_error(const char *message);

// parsing_utils2.c //
int		get_color(char *str);
bool	load_wall_texture(t_wall_texture *wall, void *mlx, char *path);
bool	load_door_texture(t_door *door, void *mlx, char *path);

// parsing_utils3.c //
bool	load_sprite_texture(t_sprite *sprite, t_data *data, char *path);

// parsing_utils4.c //
bool	check_wall_surround(t_mapdata *map_data, char **map_copy, int x, int y);
bool	check_map_valid(t_data *data);
void	setting_up_player_direction(t_data *data, int x, int y);
void	get_player_pos_direction(t_data *data);

// pasring_utils5.c //
bool	check_map_chars_valid(const char *line, bool *player_found);
bool	load_death_sprites(t_data *data);

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
bool	load_doors_and_enemies(t_data *data);

// free.c //
void	free_textures(t_data *data);
void	freeing_sprites(t_data *data);
void	free_others(t_data *data);
int		close_window(t_data *data);

// sprite.c //
void	sort_sprites(t_data *data);
void	render_sprites(t_data *data);

// sprite_utils1.c //
void	update_enemy_position_and_status(
			t_sprite_update *update, t_data *data, int i);
void	update_sprite(t_data *data, int i);
void	update_sprite_time(t_data *data, struct timeval new_time);
void	draw_sprites(t_data *data);
void	render_head_sprites(t_data *data);

// sprite_utils2.c //
void	calculate_sprite_transformations(
			t_render_sprites *sprites, t_data *data);
void	calculate_sprite_screen_position_and_size(t_render_sprites *sprites);
int		validate_texture_coordinates(t_render_sprites *sprites, t_data *data);
void	calculate_texture_y(t_render_sprites *sprites, t_data *data);
void	get_color_for_texture(t_render_sprites *sprites, t_data *data);

// sprite_utils3.c //
void	calculate_texture_x(t_render_sprites *sprites, t_data *data);
int		validate_transform_y_value(t_render_sprites *sprites);
int		process_sprite(t_render_sprites *sprites, t_data *data);
int		validate_stripes(t_render_sprites *sprites, t_data *data);
void	render_pixels(t_render_sprites *sprites, t_data *data);

#endif
