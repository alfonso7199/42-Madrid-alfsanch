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

void	count_player(t_game *game, t_point coords, t_counts *counts)
{
	game->player_x = coords.x;
	game->player_y = coords.y;
	counts->p_count++;
}

void	count_exit(t_game *game, t_point coords, t_counts *counts)
{
	game->exit_x = coords.x;
	game->exit_y = coords.y;
	counts->e_count++;
}

void	count_elements(t_game *game, char c, t_point coords, t_counts *counts)
{
	if (c == 'P')
		count_player(game, coords, counts);
	else if (c == 'E')
		count_exit(game, coords, counts);
	else if (c == 'C')
		counts->c_count++;
}
