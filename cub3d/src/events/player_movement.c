/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2025/11/20 12:35:23 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	is_wall(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map.width || y < 0 || y >= game->map.height)
		return (TRUE);
	if (game->map.grid[y][x] == '1')
		return (TRUE);
	return (FALSE);
}

//El margen puede ser muy ajustado o demasiado poco ajustado, habrá que ver
static t_bool	can_move(t_game *game, double new_x, double new_y)
{
	const double	margin = 0.2;
	int				map_x;
	int				map_y;

	map_x = (int)(new_x - margin);
	map_y = (int)(new_y - margin);
	if (is_wall(game, map_x, map_y))
		return (FALSE);
	map_x = (int)(new_x + margin);
	map_y = (int)(new_y - margin);
	if (is_wall(game, map_x, map_y))
		return (FALSE);
	map_x = (int)(new_x - margin);
	map_y = (int)(new_y + margin);
	if (is_wall(game, map_x, map_y))
		return (FALSE);
	map_x = (int)(new_x + margin);
	map_y = (int)(new_y + margin);
	if (is_wall(game, map_x, map_y))
		return (FALSE);
	return (TRUE);
}

void	move_player(t_game *game, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x + game->player.dir.x * move_x;
	new_y = game->player.pos.y + game->player.dir.y * move_x;
	new_x += game->player.plane.x * move_y;
	new_y += game->player.plane.y * move_y;
	if (can_move(game, new_x, game->player.pos.y))
		game->player.pos.x = new_x;
	if (can_move(game, game->player.pos.x, new_y))
		game->player.pos.y = new_y;
}

void	rotate_player(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir.x;
	old_plane_x = game->player.plane.x;
	game->player.dir.x = game->player.dir.x * cos(rot_speed)
		- game->player.dir.y * sin(rot_speed);
	game->player.dir.y = old_dir_x * sin(rot_speed)
		+ game->player.dir.y * cos(rot_speed);
	game->player.plane.x = game->player.plane.x * cos(rot_speed)
		- game->player.plane.y * sin(rot_speed);
	game->player.plane.y = old_plane_x * sin(rot_speed)
		+ game->player.plane.y * cos(rot_speed);
}

//Hay que llamarlo desde el loop principal
void	update_movement(t_game *game)
{
	if (game->keys.w)
		move_player(game, MOVE_SPEED, 0);
	if (game->keys.s)
		move_player(game, -MOVE_SPEED, 0);
	if (game->keys.a)
		move_player(game, 0, -MOVE_SPEED);
	if (game->keys.d)
		move_player(game, 0, MOVE_SPEED);
	if (game->keys.left)
		rotate_player(game, -ROT_SPEED);
	if (game->keys.right)
		rotate_player(game, ROT_SPEED);
}
