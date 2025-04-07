/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:50:11 by cgoh              #+#    #+#             */
/*   Updated: 2025/04/05 21:10:04 by cgoh             ###   ########.fr       */
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

static void	validating_input(int argc, char **argv)
{
	if (argc != 2 || !ft_strend(argv[1], ".cub"))
	{
		printf("Usage: ./cub3D <.cub file>\n");
		exit(EXIT_FAILURE);
	}
}

static void	set_up_mlx_hooks(t_data *data)
{
	mlx_hook(data->win, ON_DESTROY, 0, close_window, data);
	mlx_hook(data->win, ON_KEYDOWN, 1L << 0, keydown, data);
	mlx_hook(data->win, ON_MOUSEMOVE, 1L << 6, mouse_move, data);
	mlx_loop_hook(data->mlx, game_loop, data);
	mlx_loop(data->mlx);
}

int	main(int argc, char **argv)
{
	t_data	data;

	validating_input(argc, argv);
	ft_bzero(&data, sizeof(t_data));
	data.mlx = mlx_init();
	if (data.mlx == NULL)
		exit(EXIT_FAILURE);
	if (!parsing(&data, argv[1]))
		close_window(&data);
	init_data(&data);
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Cub3d");
	if (data.win == NULL)
		close_window(&data);
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	if (data.img == NULL)
		close_window(&data);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.size_line, &data.endian);
	if (data.addr == NULL)
		close_window(&data);
	set_up_mlx_hooks(&data);
	return (0);
}
