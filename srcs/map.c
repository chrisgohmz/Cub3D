/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:06:18 by apoh              #+#    #+#             */
/*   Updated: 2025/04/03 18:52:30 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	count_doors_and_enemies(t_mapdata *map_data)
{
	int	y;
	int	x;
	
	y = -1;
	while (++y < map_data->map_height)
	{
		x = -1;
		while (map_data->map[y][++x])
		{
			if (map_data->map[y][x] == 'D')
				map_data->num_doors++;
			if (map_data->map[y][x] == 'M')
				map_data->num_sprites++;
		}
	}
}

bool	check_map_chars_valid(const char *line, bool *player_found)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (!ft_strchr("01NSEWDM \n", line[i]))
		{
			ft_dprintf(STDERR_FILENO, "Error\nMap contains"
				"an invalid character\n");
			return (false);
		}
		if (ft_strchr("NSEW", line[i]))
		{
			if (!*player_found)
				*player_found = true;
			else
			{
				ft_dprintf(STDERR_FILENO, "Error\nMap must"
					"contain 1 starting position\n");
				return (false);
			}
		}
	}
	return (true);
}

static bool	read_map(t_mapdata *map_data, char **line,
	char **file_content, int fd, bool *player_found)
{
	char	*tmp;
	size_t	width;
	
	while (*line)
	{
		if (!check_map_chars_valid(*line, player_found))
			return (free(*file_content), free(*line), get_next_line(-1),
				false);
		if (!*file_content)
			*file_content = ft_strdup(*line);
		else
		{
			tmp = *file_content;
			*file_content = ft_strjoin(*file_content, *line);
			free(tmp);
		}
		if (!*file_content)
			return (false);
		map_data->map_height++;
		width = ft_strlen(*line);
		if (width > (size_t)map_data->map_width)
			map_data->map_width = width;
		free(*line);
		*line = get_next_line(fd);
	}
	return (true);
}

bool	process_map(t_data *data, char **file_content)
{
	data->map_data.map = ft_split(*file_content, '\n');
	free(*file_content);
	if (!data->map_data.map)
		return (false);
	get_player_pos_direction(data);
	if (!check_map_valid(data))
		return (false);
	return (true);
}

bool	get_map(t_data *data, char **line, char **file_content, int fd)
{
	bool	player_found;
	
	player_found = false;
	data->map_data.num_sprites = 0;
	if (!read_map(&data->map_data, line, file_content, fd, &player_found))
		return (false);
	if (!player_found)
	{
		ft_dprintf(STDERR_FILENO, "Error\nMap must contain 1 starting position\n");
		free(*file_content);
		return (false);
	}
	if (!process_map(data, file_content))
		return (false);
	count_doors_and_enemies(&data->map_data);
	if (!load_doors_and_enemies(data))
		return (false);
	return (true);
}
