/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	validate_character(t_game *game, char c)
{
	if (c != '0' && c != '1' && c != 'P' && c != 'E' && c != 'C')
	{
		free_map(game);
		error_exit("Error: Invalid character in map");
	}
}

void	validate_borders(t_game *game, char c, size_t y, size_t x)
{
	if ((y == 0 || y == game->rows - 1 || x == 0 || x == game->cols - 1))
	{
		if (c != '1')
		{
			free_map(game);
			error_exit("Error: Map borders must be walls ('1')");
		}
	}
}

void	validate_map_characters(t_game *game, t_counts *counts)
{
	size_t	y;
	size_t	x;
	char	c;
	t_point	coords;

	y = 0;
	while (y < game->rows)
	{
		x = 0;
		while (x < game->cols)
		{
			c = game->map[y][x];
			coords.y = y;
			coords.x = x;
			validate_character(game, c);
			validate_borders(game, c, y, x);
			count_elements(game, c, coords, counts);
			x++;
		}
		y++;
	}
}

void	validate_map_counts(t_game *game, t_counts *counts)
{
	if (counts->p_count != 1 || counts->e_count != 1 || counts->c_count < 1)
	{
		free_map(game);
		error_exit("Invalid map: Must have 1 P, 1 E, and at least 1 C");
	}
	game->collectibles = counts->c_count;
}

void	validate_map(t_game *game)
{
	t_counts	counts;

	counts.p_count = 0;
	counts.e_count = 0;
	counts.c_count = 0;
	validate_map_characters(game, &counts);
	validate_map_counts(game, &counts);
}
