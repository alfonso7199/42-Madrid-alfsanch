/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 11:54:56 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/11/20 12:37:34 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_bool	is_start_of_map(char *line)
{
	int	idx;

	idx = 0;
	while (line[idx] && ft_isspace(line[idx]))
		idx++;
	if (line[idx] == '1' || line[idx] == '0')
		return (TRUE);
	return (FALSE);
}

static void	validate_all_required_fields(t_game *game)
{
	if (!game->textures.north || !game->textures.east
		|| !game->textures.south || !game->textures.west)
	{
		ft_putendl_fd("Error: missing texture path", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	if (!game->colors.floor_set)
	{
		ft_putendl_fd("Error: missing floor color", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	if (!game->colors.ceiling_set)
	{
		ft_putendl_fd("Error: missing ceiling color", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
}

static void	read_all_lines_and_parse(int fd, t_game *game)
{
	char	*line;
	t_bool	in_map_section;

	in_map_section = FALSE;
	line = get_next_line(fd);
	while (line)
	{
		if (!in_map_section && is_start_of_map(line))
			in_map_section = TRUE;
		if (in_map_section)
			parse_map_line(game, line);
		else
			parse_field_line(game, line);
		free(line);
		line = get_next_line(fd);
	}
}

int	open_file(t_game *game, const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("Error: cannot open file", STDERR_FILENO);
		return (FALSE);
	}
	read_all_lines_and_parse(fd, game);
	close(fd);
	validate_all_required_fields(game);
	finalize_map(game);
	return (TRUE);
}
