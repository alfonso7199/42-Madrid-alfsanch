/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:58:17 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/11/20 12:37:39 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_map_line_characters(char *line)
{
	int	idx;

	idx = 0;
	while (line[idx])
	{
		if (!ft_strchr(" 01NSEW\n", line[idx]))
		{
			ft_putendl_fd("Error: invalid map character", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		idx++;
	}
}

static int	count_expanded_len(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			len += 4;
		else
			len++;
		i++;
	}
	return (len);
}

static char	*expand_tabs(char *line)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	*new;

	len = count_expanded_len(line);
	new = malloc(len + 1);
	if (!new)
		exit(EXIT_FAILURE);
	i = 0;
	j = 0;
	while (line[i])
	{
		k = 0;
		if (line[i] == '\t')
			while (k++ < 4)
				new[j++] = ' ';
		else
			new[j++] = line[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

void	parse_map_line(t_game *game, char *line)
{
	char	*expanded;

	expanded = expand_tabs(line);
	validate_map_line_characters(expanded);
	game->map.grid = ft_append_line(game->map.grid, expanded);
	free(expanded);
}
