/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:53:46 by apoh              #+#    #+#             */
/*   Updated: 2025/03/28 12:53:49 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	validating_commas(char *str)
{
	if (count_commas(str) != 2)
	{
		ft_dprintf(STDERR_FILENO, "Error\nFile contains invalid line\n");
		return (-1);
	}
	return (0);
}

int	validating_array_elements(char **color_rgb_arr)
{
	if (count_arr_elements(color_rgb_arr) != 3)
	{
		ft_dprintf(STDERR_FILENO, "Error\nFile contains invalid line\n");
		free_2d_arr((void ***)&color_rgb_arr);
		return (-1);
	}
	return (0);
}

int	get_color(char *str)
{
	char	**color_rgb_arr;
	int		red;
	int		green;
	int		blue;

	if (validating_commas(str) == -1)
		return (-1);
	color_rgb_arr = ft_split(str, ',');
	if (!color_rgb_arr)
		return (-1);
	if (validating_array_elements(color_rgb_arr) == -1)
		return (-1);
	if (!check_color_range(&red, color_rgb_arr[0])
		|| !check_color_range(&green, color_rgb_arr[1])
		|| !check_color_range(&blue, color_rgb_arr[2]))
	{
		free_2d_arr((void ***)&color_rgb_arr);
		return (-1);
	}
	free_2d_arr((void ***)&color_rgb_arr);
	return (red << 16 | green << 8 | blue);
}

bool	get_texture(t_wall_texture *wall, t_data *data, char *path)
{
	if (wall->img)
		mlx_destroy_image(data->mlx, wall->img);
	wall->img = mlx_xpm_file_to_image(data->mlx, path,
			&wall->img_width, &wall->img_height);
	if (!wall->img)
	{
		ft_dprintf(STDERR_FILENO, "Error\nFailed to load texture file\n");
		return (false);
	}
	wall->addr = mlx_get_data_addr(wall->img, &wall->bits_per_pixel,
			&wall->size_line, &wall->endian);
	if (!wall->addr)
	{
		ft_dprintf(STDERR_FILENO, "Error\nFailed to get image data"
			"address: %s\n", path);
		mlx_destroy_image(data->mlx, wall->img);
		return (false);
	}
	return (true);
}

bool	load_door_texture(t_data *data)
{
	char	*door_texture_path;

	door_texture_path = "./textures/door/Door.xpm";
	return (get_texture(&data->map_data.door_texture, data, door_texture_path));
}
