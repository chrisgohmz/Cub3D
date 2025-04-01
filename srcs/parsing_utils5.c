/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:06:18 by apoh              #+#    #+#             */
/*   Updated: 2025/04/01 21:56:39 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

bool	get_map(t_data *data)
{
	size_t	width;
	int		y;
	int		x;
	int		door_index;
	bool	player_found;
	int	sprite_index;
	
	y = 0;
	x = 0;
	player_found = false;
	sprite_index = 0;
	data->map_data.num_sprites = 0;
	while (data->map_data.line)
	{
		if (!check_map_chars_valid(data->map_data.line, &player_found))
		{
			free(data->map_data.file_content);
			free(data->map_data.line);
			get_next_line(-1);
			return (false);
		}
		if (!data->map_data.file_content)
			data->map_data.file_content = ft_strdup(data->map_data.line);
		else
		{
			data->map_data.tmp = data->map_data.file_content;
			data->map_data.file_content = ft_strjoin(data->map_data.file_content, data->map_data.line);
			free(data->map_data.tmp);
		}
		if (!data->map_data.file_content)
			return (false);
		data->map_data.map_height++;
		width = ft_strlen(data->map_data.line);
		if (width > (size_t)data->map_data.map_width)
			data->map_data.map_width = width;
		free(data->map_data.line);
		data->map_data.line = get_next_line(data->map_data.fd);
	}
	if (!player_found)
	{
		ft_dprintf(STDERR_FILENO, "Error\nMap must contain 1 starting position\n");
		free(data->map_data.file_content);
		return (false);
	}
	data->map_data.map = ft_split(data->map_data.file_content, '\n');
	free(data->map_data.file_content);
	if (!data->map_data.map)
		return (false);
	get_player_pos_direction(data);
	if (!check_map_valid(data))
		return (false);
	data->map_data.num_doors = 0;
	while (y < data->map_data.map_height)
	{
		x = -1;
		while (data->map_data.map[y][++x])
		{
			if (data->map_data.map[y][x] == 'D')
				data->map_data.num_doors++;
			if (data->map_data.map[y][x] == 'M')
				data->map_data.num_sprites++;
		}
		y++;
	}
	data->map_data.door_x = malloc(sizeof(int) * data->map_data.num_doors);
	data->map_data.door_y = malloc(sizeof(int) * data->map_data.num_doors);
	data->map_data.door_states = malloc(sizeof(bool) * data->map_data.num_doors);
	if (!data->map_data.door_x || !data->map_data.door_y || !data->map_data.door_states)
		return (false);
	data->map_data.sprites = ft_calloc(data->map_data.num_sprites, sizeof(t_sprite));
	if (!data->map_data.sprites)
		return (false);
	y = 0;
	door_index = 0;
	while (y < data->map_data.map_height)
	{
		x = -1;
		while (data->map_data.map[y][++x])
		{
			if (data->map_data.map[y][x] == 'D')
			{
				data->map_data.door_x[door_index] = x;
				data->map_data.door_y[door_index] = y;
				data->map_data.door_states[door_index] = false;
				door_index++;
			}
			if (data->map_data.map[y][x] == 'M')
			{
				data->map_data.sprites[sprite_index].x = x;
				data->map_data.sprites[sprite_index].y = y;
				if (!load_sprite_texture(&data->map_data.sprites[sprite_index], data, "./textures/sprites/golden_freddy.xpm"))
					return (false);
				printf("Sprite %d initialized at (%d, %d)\n", sprite_index, x, y);
				sprite_index++;
			}
		}
		y++;
	}
	if (door_index != data->map_data.num_doors)
		return (false);	
	return (true);
}
