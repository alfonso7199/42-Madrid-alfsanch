/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_game *game)
{
	size_t	i;

	if (game->map)
	{
		i = 0;
		while (i < game->rows)
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
		game->map = NULL;
	}
}

void	free_temp_map(char **temp_map, size_t rows)
{
	size_t	i;

	i = 0;
	while (i < rows)
	{
		free(temp_map[i]);
		i++;
	}
	free(temp_map);
}
