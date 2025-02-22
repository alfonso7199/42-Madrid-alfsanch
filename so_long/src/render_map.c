/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

static void	render_floor(t_game *game)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < game->rows)
	{
		x = 0;
		while (x < game->cols)
		{
			mlx_put_image_to_window(game->mlx, game->win, game->floor,
				x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

void	render_map(t_game *game)
{
	size_t	y;
	size_t	x;

	mlx_clear_window(game->mlx, game->win);
	render_floor(game);
	y = 0;
	while (y < game->rows)
	{
		x = 0;
		while (x < game->cols)
		{
			render_tile(game, y, x);
			x++;
		}
		y++;
	}
}
