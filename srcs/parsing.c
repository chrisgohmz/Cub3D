/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:58:40 by apoh              #+#    #+#             */
/*   Updated: 2025/04/03 21:59:44 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	found_map_start(const char *str)
{
	int	i;

	i = -1;
	while (str[++i] == ' ')
	{
	}
	return (str[i] == '1');
}

static bool	read_file_lines_except_map(int fd,
	char **file_content, char **line)
{
	char	*tmp;

	*line = get_next_line(fd);
	while (*line && !found_map_start(*line))
	{
		if (!*file_content)
			*file_content = *line;
		else
		{
			tmp = *file_content;
			*file_content = ft_strjoin(*file_content, *line);
			free(tmp);
			free(*line);
			if (!*file_content)
				return (false);
		}
		*line = get_next_line(fd);
	}
	if (!*file_content)
	{
		ft_dprintf(STDERR_FILENO, "Error\nFile is empty\n");
		close(fd);
		return (false);
	}
	return (true);
}

int	parsing(t_data *data, char *file_path)
{
	int		fd;
	char	*file_content;
	char	*line;

	ft_bzero(&data->map_data, sizeof(t_mapdata));
	file_content = NULL;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, "Error\nFailed to open %s\n", file_path);
		return (0);
	}
	if (!read_file_lines_except_map(fd, &file_content, &line))
		return (0);
	if (!split_elements_and_extract_info(&data->map_data,
			&file_content, data->mlx))
		return (free(line), close(fd), 0);
	if (!get_map(data, &line, &file_content, fd))
		return (close(fd), 0);
	if (!load_doors_and_enemies(data))
		return (close(fd), 0);
	if (!load_death_sprites(data))
		return (close(fd), 0);
	close(fd);
	return (1);
}
