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
