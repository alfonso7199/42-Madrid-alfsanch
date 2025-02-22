/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	render_wall(t_game *game, size_t y, size_t x)
{
	mlx_put_image_to_window(game->mlx, game->win, game->wall,
		x * TILE_SIZE, y * TILE_SIZE);
}

void	render_collectible(t_game *game, size_t y, size_t x)
{
	mlx_put_image_to_window(game->mlx, game->win, game->collectible,
		x * TILE_SIZE, y * TILE_SIZE);
}

void	render_exit(t_game *game, size_t y, size_t x)
{
	if (game->collectibles == 0)
		mlx_put_image_to_window(game->mlx, game->win, game->exit2,
			x * TILE_SIZE, y * TILE_SIZE);
	else
		mlx_put_image_to_window(game->mlx, game->win, game->exit,
			x * TILE_SIZE, y * TILE_SIZE);
}

void	render_player(t_game *game, size_t y, size_t x)
{
	void	*player_sprite;

	if (game->direction == 0)
		player_sprite = game->player_up[game->current_frame];
	else if (game->direction == 1)
		player_sprite = game->player_down[game->current_frame];
	else if (game->direction == 2)
		player_sprite = game->player_left[game->current_frame];
	else if (game->direction == 3)
		player_sprite = game->player_right[game->current_frame];
	mlx_put_image_to_window(game->mlx, game->win, player_sprite,
		x * TILE_SIZE, y * TILE_SIZE);
}

void	render_tile(t_game *game, size_t y, size_t x)
{
	if (game->map[y][x] == '1')
		render_wall(game, y, x);
	else if (game->map[y][x] == 'C')
		render_collectible(game, y, x);
	else if (game->map[y][x] == 'E')
		render_exit(game, y, x);
	else if (game->map[y][x] == 'P')
		render_player(game, y, x);
}
