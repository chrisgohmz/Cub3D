/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:20:39 by apoh              #+#    #+#             */
/*   Updated: 2025/04/11 22:01:12 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	storing_sprites_spawning_point(t_game *game, t_data *data)
{
	game->i = 0;
	while (game->i < data->map_data.num_sprites)
	{
		data->map_data.sprites[game->i].original_x
			= (int)data->map_data.sprites[game->i].x;
		data->map_data.sprites[game->i].original_y
			= (int)data->map_data.sprites[game->i].y;
		game->i++;
	}
}

void	sprites_position_update(t_game *game, t_data *data)
{
	game->old_x = (int)data->map_data.sprites[game->i].x;
	game->old_y = (int)data->map_data.sprites[game->i].y;
	update_sprite(data, game->i);
	game->new_x = (int)data->map_data.sprites[game->i].x;
	game->new_y = (int)data->map_data.sprites[game->i].y;
}

int	game_loop(t_data *data)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	storing_sprites_spawning_point(&game, data);
	game.i = 0;
	while (game.i < data->map_data.num_sprites && !data->map_data.dead)
	{
		sprites_position_update(&game, data);
		if (game.new_x != game.old_x || game.new_y != game.old_y)
		{
			if (data->map_data.sprites[game.i].original_cell == 'D')
				data->map_data.map[game.old_y][game.old_x]
					= data->map_data.sprites[game.i].original_cell;
			else if (game.new_x != data->map_data.sprites[game.i].original_x
				|| game.new_y != data->map_data.sprites[game.i].original_y)
				data->map_data.map[game.old_y][game.old_x] = '0';
			data->map_data.sprites[game.i].original_cell
				= data->map_data.map[game.new_y][game.new_x];
			data->map_data.map[game.new_y][game.new_x] = 'M';
		}
		game.i++;
	}
	render_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
