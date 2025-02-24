/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:50:11 by cgoh              #+#    #+#             */
/*   Updated: 2025/02/22 19:51:56 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	close_window(t_data *data)
{
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
	printf("Initialising Window\n");
	ft_memset(&data, 0, sizeof(t_data));
	ft_memcpy(data.map, map_array, sizeof(map_array));
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
		exit(EXIT_FAILURE);
	}
	print_map(&data);
	mlx_hook(data.win, 17, 0, (int (*)(void *))close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
