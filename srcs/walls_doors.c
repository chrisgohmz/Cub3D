/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_doors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:33:59 by cgoh              #+#    #+#             */
/*   Updated: 2025/04/02 21:39:01 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	load_door_texture(t_data *data)
{
	char	*door_texture_path;

	door_texture_path = "./textures/door/Door.xpm";
	return (get_texture(&data->map_data.door_texture, data, door_texture_path));
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
