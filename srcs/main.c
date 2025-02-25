/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:50:11 by cgoh              #+#    #+#             */
/*   Updated: 2025/02/24 21:29:31 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_data(t_data *data)
{
	data->player_pos.x = 3;
	data->player_pos.y = 3;
	data->player_direction.x = -1;
	data->player_direction.y = 0;
	data->camera_plane_pos.x = 0;
	data->camera_plane_pos.y = 0.66;
}

static int	close_window(t_data *data)
{
	if (data->img != NULL)
	{
		mlx_destroy_image(data->mlx, data->img);
		data->img = NULL;
	}
	if (data->win != NULL)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	if (data->mlx != NULL)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
	exit(EXIT_SUCCESS);
}

static void	print_map(t_data *data)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 6)
		{
			printf("%c ", data->map[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}	
}

static void	render_map(t_data *data)
{
	int	x;
	int	y;
	int	block_size_x;
	int	block_size_y;
	int	color;
	int	i;
	int	j;
	int	pixel;
	int	line_color;
	int	player_screen_x;
	int	player_screen_y;
	int	player_radius;
	int	player_color;
	int	py;
	int	px;
	double	dirX;
	double	dirY;
	double	rayLength;
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

	block_size_x = 1920 / 6;
	block_size_y = 1080 / 5;
	line_color = 0xFFFFFF;
	y = 0;
	// this is for adding colour to each cell //
	while (y < 5)
	{
		x = 0;
		while (x < 6)
		{
			if (data->map[y][x] == '1')
				color = 0x808080;
			else
				color = 0x000000;
			i = 0;
			while (i < block_size_x)
			{
				j = 0;
				while (j < block_size_y)
				{
					pixel = ((y * block_size_y + j) * data->size_line) + ((x* block_size_x + i) * (data->bits_per_pixel / 8));
					*(unsigned int*)((char*)data->addr + pixel) = color;
					j++;
				}
				i++;
			}
			x++;
		}	
		y++;
	}
	// this is for drawing lines for each cell //
	y = 0;
	while (y <= 5)
	{
		i = 0;
		while (i < 1920)
		{
			pixel = (y * block_size_y * data->size_line) + (i * (data->bits_per_pixel / 8));
			*(unsigned int*)((char*)data->addr + pixel) = line_color;
			i++;
		}
		y++;
	}
	x = 0;
	while (x <= 6)
	{
		j = 0;
		while (j < 1080)
		{
			pixel = (j * data->size_line) + (x * block_size_x  * (data->bits_per_pixel / 8));
			*(unsigned int*)((char*)data->addr + pixel) = line_color;
			j++;
		}
		x++;
	}
	// this is for drawing a dot for the player coordinates, but shifting it to the middle of the cell for realistic purposes //
	player_screen_x = data->player_pos.x * block_size_x + (block_size_x / 2);
	player_screen_y = data->player_pos.y * block_size_y + (block_size_y / 2);
	player_radius = 5;
	player_color = 0xFF0000;
	py = -player_radius;
	while (py <= player_radius)
	{
		px = -player_radius;
		while(px <= player_radius)
		{
			if (px * px + py * py <= player_radius * player_radius)
			{
				pixel = ((player_screen_y + py) * data->size_line) + ((player_screen_x + px) * (data->bits_per_pixel / 8));
				*(unsigned int*)((char*)data->addr + pixel) = player_color;
			}
			px++;
		}
		py++;
	}
	// this is to draw the ray out //
	dirX = data->player_direction.x;
	dirY = data->player_direction.y;
	rayLength = 1000;
	ray_end_x = player_screen_x + (int)(dirX * rayLength);
	ray_end_y = player_screen_y + (int)(dirY * rayLength);
	dx = abs(ray_end_x - player_screen_x);
	dy = abs(ray_end_y - player_screen_y);
	
	if (player_screen_x < ray_end_x)
		sx = 1;
	else
		sx = -1;
	if (player_screen_y < ray_end_y)
		sy = 1;
	else
		sy = -1;
	err = dx - dy;
	current_x = player_screen_x;
	current_y = player_screen_y;
	while (1)
	{
		if (current_x >= 0 && current_x < 1920 && current_y >= 0 && current_y < 1080)
		{
			pixel = (current_y * data->size_line) + (current_x *(data->bits_per_pixel / 8));
			*(unsigned int*)((char*)data->addr + pixel) = 0x00FF00;
		}
		if (current_x == ray_end_x && current_y == ray_end_y)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err = err - dy;
			current_x = current_x + sx;
		}
		if (e2 < dx)
		{
			err = err + dx;
			current_y = current_y + sy;
		}
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	char map_array[5][6] = {  
		{'1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '1'},
		{'1', '0', '0', 'N', '0', '1'},
		{'1', '1', '1', '1', '1', '1'},
		};
	(void)argc;
	(void)argv;
	ft_memset(&data, 0, sizeof(t_data));
	ft_memcpy(data.map, map_array, sizeof(map_array));
	init_data(&data);
	printf("Initialising Window\n");
	data.mlx = mlx_init();
	if (data.mlx == NULL)
	{
		perror("Failed to initialise window");
		exit(EXIT_FAILURE);
	}
	printf("Creating Window\n");
	data.win = mlx_new_window(data.mlx, 1920, 1080, "Cub3d");
	if (data.win == NULL)
	{
		perror("Failed to create window");
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		data.mlx = NULL;
		exit(EXIT_FAILURE);
	}
	print_map(&data);
	data.img = mlx_new_image(data.mlx, 1920, 1080);
	if (data.img == NULL)
	{
		perror("Failed to create image");
		mlx_destroy_window(data.mlx, data.win);
		data.win = NULL;
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		data.mlx = NULL;
		exit(EXIT_FAILURE);
	}
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.size_line, &data.endian);
	if (data.addr == NULL)
	{
		perror("Failed to get data address");
		mlx_destroy_image(data.mlx, data.img);
		data.img = NULL;
		mlx_destroy_window(data.mlx, data.win);
		data.win = NULL;
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		data.mlx = NULL;
		exit(EXIT_FAILURE);
	}
	render_map(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_hook(data.win, 17, 0, (int (*)(void *))close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
