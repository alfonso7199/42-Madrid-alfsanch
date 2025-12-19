/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 09:23:52 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/11/20 12:37:50 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_bool	is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (TRUE);
	return (FALSE);
}

static void	process_player_position(t_game *game, int x, int y,
int *player_count)
{
	if (*player_count == 0)
		init_player(game, x, y, game->map.grid[y][x]);
	(*player_count)++;
	game->map.grid[y][x] = '0';
}

static int	count_and_replace_players(t_game *game)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (is_player_char(game->map.grid[y][x]))
				process_player_position(game, x, y, &count);
			x++;
		}
		y++;
	}
	return (count);
}

static void	validate_map_integrity(t_game *game, int player_count)
{
	if (player_count != 1)
	{
		ft_putendl_fd("Error: invalid player count", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	if (!is_map_closed(&game->map))
	{
		ft_putendl_fd("Error: map is not closed", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	finalize_map(t_game *game)
{
	int	player_count;

	normalize_map_with_spaces(&game->map);
	player_count = count_and_replace_players(game);
	validate_map_integrity(game, player_count);
}
