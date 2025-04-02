/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:58:40 by apoh              #+#    #+#             */
/*   Updated: 2025/04/02 21:30:20 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	load_head_sprites(t_data *data)
{
	if (!load_sprite_texture(data->map_data.head_sprites, data, "./textures/sprites/golden_freddy.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 1, data, "./textures/sprites/golden_freddy.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 2, data, "./textures/sprites/golden_freddy.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 3, data, "./textures/sprites/golden_freddy.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 4, data, "./textures/sprites/golden_freddy.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 5, data, "./textures/sprites/golden_freddy.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 6, data, "./textures/sprites/golden_freddy.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 7, data, "./textures/sprites/golden_freddy.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 8, data, "./textures/sprites/golden_freddy.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 9, data, "./textures/sprites/golden_freddy.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 10, data, "./textures/sprites/golden_freddy.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 11, data, "./textures/sprites/golden_freddy.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 12, data, "./textures/sprites/golden_freddy.xpm"))
		return (false);
	return (true);
}

static bool	found_map_start(const char *str)
{
	int	i;

	i = -1;
	while (str[++i] == ' ')
	{
	}
	return (str[i] == '1');
}

static bool	read_file_lines_except_map(t_mapdata *map_data, int fd,
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
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, "Error\nFailed to open %s\n", file_path);
		return (0);
	}
	if (!read_file_lines_except_map(&data->map_data, fd, &file_content, &line))
		return (0);
	if (!split_elements_and_extract_info(&data->map_data, &file_content, mlx))
		return (free(line), close(fd), 0);
	if (!get_map(data))
		return (close(fd), 0);
	if (!load_door_texture(data))
		return (close(fd), 0);
	if (!load_head_sprites(data))
		return (close(fd), 0);
	close(fd);
	return (1);
}
