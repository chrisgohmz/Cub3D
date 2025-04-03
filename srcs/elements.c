/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:59:40 by cgoh              #+#    #+#             */
/*   Updated: 2025/04/03 18:51:11 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	check_for_textures_and_colors(t_mapdata *map_data)
{
	if (!map_data->north_texture.img)
	{
		ft_dprintf(STDERR_FILENO, "Error\nMissing north wall texture\n");
		return (false);
	}
	else if (!map_data->south_texture.img)
	{
		ft_dprintf(STDERR_FILENO, "Error\nMissing south wall texture\n");
		return (false);
	}
	else if (!map_data->west_texture.img)
	{
		ft_dprintf(STDERR_FILENO, "Error\nMissing west wall texture\n");
		return (false);
	}
	else if (!map_data->east_texture.img)
		return (ft_dprintf(STDERR_FILENO, "Error\nMissing east wall texture\n"),
			false);
	else if (map_data->ceiling_colour == -1)
		return (ft_dprintf(STDERR_FILENO, "Error\nMissing ceiling colour\n"),
			false);
	else if (map_data->floor_colour == -1)
		return (ft_dprintf(STDERR_FILENO, "Error\nMissing floor colour\n"),
			false);
	return (true);
}

static bool	check_line_is_color_identifier(t_mapdata *map_data,
	char **element_info)
{
	if (!ft_strncmp(element_info[0], FLOOR, sizeof(FLOOR)))
	{
		map_data->floor_colour = get_color(element_info[1]);
		if (map_data->floor_colour == -1)
			return (false);
	}
	else if (!ft_strncmp(element_info[0], CEILING, sizeof(CEILING)))
	{
		map_data->ceiling_colour = get_color(element_info[1]);
		if (map_data->ceiling_colour == -1)
			return (false);
	}
	else
	{
		ft_dprintf(STDERR_FILENO, "Error\nFile contains invalid line\n");
		return (false);
	}
	return (true);
}

static bool	check_line_is_wall_or_color_identifier(t_mapdata *map_data,
	char **element_info, void *mlx)
{
	if (!ft_strncmp(element_info[0], NORTH, sizeof(NORTH)))
		return (get_texture(&map_data->north_texture, mlx, element_info[1]));
	else if (!ft_strncmp(element_info[0], SOUTH, sizeof(SOUTH)))
		return (get_texture(&map_data->south_texture, mlx, element_info[1]));
	else if (!ft_strncmp(element_info[0], EAST, sizeof(EAST)))
		return (get_texture(&map_data->east_texture, mlx, element_info[1]));
	else if (!ft_strncmp(element_info[0], WEST, sizeof(WEST)))
		return (get_texture(&map_data->west_texture, mlx, element_info[1]));
	return (check_line_is_color_identifier(map_data, element_info));
}

static bool	get_element_info(t_mapdata *map_data, char **elements, void *mlx)
{
	int		i;
	char	**element_info;

	map_data->ceiling_colour = -1;
	map_data->floor_colour = -1;
	i = -1;
	while (elements[++i])
	{
		element_info = ft_split(elements[i], ' ');
		if (!element_info)
			return (false);
		if (count_arr_elements(element_info) == 2)
		{
			if (!check_line_is_wall_or_color_identifier(map_data,
					element_info, mlx))
				return (free_2d_arr((void ***)&element_info), false);
		}
		else
		{
			ft_dprintf(STDERR_FILENO, "Error\nFile contains invalid line\n");
			return (free_2d_arr((void ***)&element_info), false);
		}
		free_2d_arr((void ***)&element_info);
	}
	return (check_for_textures_and_colors(map_data));
}

bool	split_elements_and_extract_info(t_mapdata *map_data,
	char **file_content, void *mlx)
{
	char	**elements;

	elements = ft_split(*file_content, '\n');
	free(*file_content);
	*file_content = NULL;
	if (!elements)
		return (false);
	if (!get_element_info(map_data, elements, mlx))
	{
		get_next_line(-1);
		free_2d_arr((void ***)&elements);
		return (false);
	}
	free_2d_arr((void ***)&elements);
	return (true);
}
