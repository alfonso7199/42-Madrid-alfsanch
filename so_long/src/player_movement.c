/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

static void	update_player_position(t_game *game, int new_x, int new_y)
{
	if (game->on_exit)
		game->map[game->player_y][game->player_x] = 'E';
	else
		game->map[game->player_y][game->player_x] = '0';
	game->on_exit = (game->map[new_y][new_x] == 'E');
	game->player_x = new_x;
	game->player_y = new_y;
	game->map[new_y][new_x] = 'P';
}

static void	handle_collectible(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == 'C')
		game->collectibles--;
	if (game->map[new_y][new_x] == 'E' && game->collectibles == 0)
	{
		printf("¡Has ganado!\n");
		close_game(game);
	}
}

void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	if (game->map[new_y][new_x] == '1')
		return ;
	handle_collectible(game, new_x, new_y);
	update_player_position(game, new_x, new_y);
	if (dy == -1)
		game->direction = 0;
	else if (dy == 1)
		game->direction = 1;
	else if (dx == -1)
		game->direction = 2;
	else if (dx == 1)
		game->direction = 3;
	game->current_frame = (game->current_frame + 1) % 4;
	game->moves++;
	printf("Movimientos: %d\n", game->moves);
	render_map(game);
}
