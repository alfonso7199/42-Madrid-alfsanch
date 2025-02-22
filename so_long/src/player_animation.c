/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	load_player_up_frames(t_game *game, int tile_size)
{
	game->player_up[0] = mlx_xpm_file_to_image(game->mlx,
			"textures/player_up_1.xpm", &tile_size, &tile_size);
	game->player_up[1] = mlx_xpm_file_to_image(game->mlx,
			"textures/player_up_2.xpm", &tile_size, &tile_size);
	game->player_up[2] = mlx_xpm_file_to_image(game->mlx,
			"textures/player_up_3.xpm", &tile_size, &tile_size);
	game->player_up[3] = mlx_xpm_file_to_image(game->mlx,
			"textures/player_up_4.xpm", &tile_size, &tile_size);
}

static void	load_player_down_frames(t_game *game, int tile_size)
{
	game->player_down[0] = mlx_xpm_file_to_image(game->mlx,
			"textures/player_down_1.xpm", &tile_size, &tile_size);
	game->player_down[1] = mlx_xpm_file_to_image(game->mlx,
			"textures/player_down_2.xpm", &tile_size, &tile_size);
	game->player_down[2] = mlx_xpm_file_to_image(game->mlx,
			"textures/player_down_3.xpm", &tile_size, &tile_size);
	game->player_down[3] = mlx_xpm_file_to_image(game->mlx,
			"textures/player_down_4.xpm", &tile_size, &tile_size);
}

static void	load_player_left_frames(t_game *game, int tile_size)
{
	game->player_left[0] = mlx_xpm_file_to_image(game->mlx,
			"textures/player_left_1.xpm", &tile_size, &tile_size);
	game->player_left[1] = mlx_xpm_file_to_image(game->mlx,
			"textures/player_left_2.xpm", &tile_size, &tile_size);
	game->player_left[2] = mlx_xpm_file_to_image(game->mlx,
			"textures/player_left_3.xpm", &tile_size, &tile_size);
	game->player_left[3] = mlx_xpm_file_to_image(game->mlx,
			"textures/player_left_4.xpm", &tile_size, &tile_size);
}

static void	load_player_right_frames(t_game *game, int tile_size)
{
	game->player_right[0] = mlx_xpm_file_to_image(game->mlx,
			"textures/player_right_1.xpm", &tile_size, &tile_size);
	game->player_right[1] = mlx_xpm_file_to_image(game->mlx,
			"textures/player_right_2.xpm", &tile_size, &tile_size);
	game->player_right[2] = mlx_xpm_file_to_image(game->mlx,
			"textures/player_right_3.xpm", &tile_size, &tile_size);
	game->player_right[3] = mlx_xpm_file_to_image(game->mlx,
			"textures/player_right_4.xpm", &tile_size, &tile_size);
}

void	load_player_animation(t_game *game)
{
	int	tile_size;
	int	i;

	tile_size = TILE_SIZE;
	load_player_up_frames(game, tile_size);
	load_player_down_frames(game, tile_size);
	load_player_left_frames(game, tile_size);
	load_player_right_frames(game, tile_size);
	i = 0;
	while (i < 4)
	{
		if (!game->player_up[i] || !game->player_down[i]
			|| !game->player_left[i] || !game->player_right[i])
			error_exit("Error: Failed to load player animation textures.");
		i++;
	}
	game->current_frame = 0;
	game->direction = 1;
}
