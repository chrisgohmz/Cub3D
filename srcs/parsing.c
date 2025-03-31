/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:58:40 by apoh              #+#    #+#             */
/*   Updated: 2025/03/31 20:05:44 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	load_head_sprites(t_data *data)
{
	if (!load_sprite_texture(data->map_data.head_sprites, data, "./textures/sprites/golden_freddy_head1.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 1, data, "./textures/sprites/golden_freddy_head2.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 2, data, "./textures/sprites/golden_freddy_head3.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 3, data, "./textures/sprites/golden_freddy_head4.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 4, data, "./textures/sprites/golden_freddy_head5.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 5, data, "./textures/sprites/golden_freddy_head6.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 6, data, "./textures/sprites/golden_freddy_head7.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 7, data, "./textures/sprites/golden_freddy_head8.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 8, data, "./textures/sprites/golden_freddy_head9.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 9, data, "./textures/sprites/golden_freddy_head10.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 10, data, "./textures/sprites/golden_freddy_head11.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 11, data, "./textures/sprites/golden_freddy_head12.xpm"))
		return (false);
	else if (!load_sprite_texture(data->map_data.head_sprites + 12, data, "./textures/sprites/golden_freddy_head13.xpm"))
		return (false);
	return (true);
}

int	parsing(t_data *data, char *file_path)
{	
	ft_bzero(&data->map_data, sizeof(t_mapdata));
	data->map_data.fd = open(file_path, O_RDONLY);
	if (data->map_data.fd == -1)
	{
		ft_dprintf(STDERR_FILENO, "Error\nFailed to open %s\n", file_path);
		return (0);
	}
	data->map_data.line = get_next_line(data->map_data.fd);
	while (data->map_data.line && !found_map_start(data->map_data.line))
	{
		if (!data->map_data.file_content)
			data->map_data.file_content = data->map_data.line;
		else
		{
			data->map_data.tmp = data->map_data.file_content;
			data->map_data.file_content = ft_strjoin(data->map_data.file_content, data->map_data.line);
			free(data->map_data.tmp);
			free(data->map_data.line);
			if (!data->map_data.file_content) // handling ft_strjoin failure //
				return (0);
		}
		data->map_data.line = get_next_line(data->map_data.fd);
	}
	if (!data->map_data.file_content)
	{
		ft_dprintf(STDERR_FILENO, "Error\nFile is empty\n");
		close(data->map_data.fd);
		return (0);
	}
	data->map_data.elements = ft_split(data->map_data.file_content, '\n'); // split the data up by new line //
	free(data->map_data.file_content);
	data->map_data.file_content = NULL;
	if (!data->map_data.elements) // if ft_split fails //
		return (0);
	if (!get_element_info(data))
	{
		get_next_line(-1);
		free(data->map_data.line);
		free_2d_arr((void ***)&data->map_data.elements);
		return (close(data->map_data.fd), 0);
	}
	free_2d_arr((void ***)&data->map_data.elements);
	if (!get_map(data))
		return (close(data->map_data.fd), 0);
	if (!load_door_texture(data))
		return (close(data->map_data.fd), 0);
	if (!load_head_sprites(data))
		return (close(data->map_data.fd), 0);
	close(data->map_data.fd);
	return (1);
}
