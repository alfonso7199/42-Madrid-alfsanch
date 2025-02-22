/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	process_line(t_game *game, char *line)
{
	size_t	len;
	char	**new_map;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	new_map = realloc(game->map, (game->rows + 1) * sizeof(char *));
	if (!new_map)
	{
		close(game->fd);
		error_exit("Error: Failed to allocate memory for map");
	}
	game->map = new_map;
	game->map[game->rows++] = line;
}

void	load_map(t_game *game, const char *filename)
{
	char	*line;

	game->fd = open(filename, O_RDONLY);
	if (game->fd < 0)
		error_exit("Error: Failed to open map file");
	game->rows = 0;
	while (1)
	{
		line = get_next_line(game->fd);
		if (!line)
			break ;
		process_line(game, line);
	}
	close(game->fd);
	if (game->rows == 0)
		error_exit("Error: Map is empty");
	game->cols = ft_strlen(game->map[0]);
	validate_map(game);
}
