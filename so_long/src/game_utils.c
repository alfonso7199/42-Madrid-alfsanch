/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	load_textures(t_game *game, int tile_size)
{
	game->wall = mlx_xpm_file_to_image(game->mlx,
			"textures/wall.xpm", &tile_size, &tile_size);
	game->player = mlx_xpm_file_to_image(game->mlx,
			"textures/player.xpm", &tile_size, &tile_size);
	game->collectible = mlx_xpm_file_to_image(game->mlx,
			"textures/collectible.xpm", &tile_size, &tile_size);
	game->exit = mlx_xpm_file_to_image(game->mlx,
			"textures/exit.xpm", &tile_size, &tile_size);
	game->exit2 = mlx_xpm_file_to_image(game->mlx,
			"textures/exit2.xpm", &tile_size, &tile_size);
	game->floor = mlx_xpm_file_to_image(game->mlx,
			"textures/tile1.xpm", &tile_size, &tile_size);
	if (!game->wall || !game->player || !game->collectible || !game->exit)
		error_exit("Error: Failed to load textures.");
}

void	init_game(t_game *game)
{
	int	tile_size;

	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->cols * TILE_SIZE,
			game->rows * TILE_SIZE, "so_long");
	tile_size = TILE_SIZE;
	load_player_animation(game);
	game->on_exit = 0;
	load_textures(game, tile_size);
	render_map(game);
}
