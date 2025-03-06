/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:50:11 by cgoh              #+#    #+#             */
/*   Updated: 2025/03/06 22:13:30 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;

	dest = (char *)data->addr + (y * data->size_line + x
			* (data->bits_per_pixel / 8));
	*((unsigned int *)dest) = color;
}

int	main(int argc, char **argv)
{
	t_data	data;
	
	if (argc != 2)
	{
		printf("Usage: ./cub3D <.cub file>\n");
		exit(EXIT_FAILURE);
	}
	if (parsing(&data, argv[1]) == -1)
	{
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
	ft_memset(&data, 0, sizeof(t_data));
	init_data(&data);
	data.mlx = mlx_init();
	if (data.mlx == NULL)
	{
		perror("Failed to initialise window");
		exit(EXIT_FAILURE);
	}
	printf("Creating Window\n");
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Cub3d");
	if (data.win == NULL)
	{
		perror("Failed to create window");
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		data.mlx = NULL;
		exit(EXIT_FAILURE);
	}
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
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
	mlx_hook(data.win, ON_DESTROY, 0, close_window, &data);
	mlx_hook(data.win, ON_KEYDOWN, 1L << 0, keydown, &data);
	mlx_loop(data.mlx);
	return (0);
}
