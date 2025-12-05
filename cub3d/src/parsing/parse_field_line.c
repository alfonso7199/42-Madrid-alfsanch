/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_field_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:46:50 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/11/20 12:36:34 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*dup_trim_path(char *path)
{
	char	*path_raw;
	char	*path_trim;

	path_raw = ft_strdup(path);
	if (!path_raw)
		return (NULL);
	path_trim = ft_strtrim(path_raw, " \n\r\t");
	free(path_raw);
	return (path_trim);
}

static void	assign_texture(char **dst, char *src)
{
	if (*dst != NULL)
	{
		ft_putendl_fd("Error: duplicated texture key", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	*dst = dup_trim_path(src);
	if (!*dst || **dst == '\0')
	{
		ft_putendl_fd("Error: empty texure path", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
}

static void	assign_color(t_colors *colors, char *line, t_bool is_floor)
{
	if (is_floor && colors->floor_set)
	{
		ft_putendl_fd("Error: duplicated floor color", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	if (!is_floor && colors->ceiling_set)
	{
		ft_putendl_fd("Error: duplicated ceiling color", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	parse_color(colors, line, is_floor);
	if (is_floor)
		colors->floor_set = TRUE;
	else
		colors->ceiling_set = TRUE;
}

void	parse_field_line(t_game *game, char *line)
{
	if (!line || *line == '\n' || *line == '\0')
		return ;
	if (!ft_strncmp(line, "NO ", 3))
		assign_texture(&game->textures.north, line + 3);
	else if (!ft_strncmp(line, "SO ", 3))
		assign_texture(&game->textures.south, line + 3);
	else if (!ft_strncmp(line, "WE ", 3))
		assign_texture(&game->textures.west, line + 3);
	else if (!ft_strncmp(line, "EA ", 3))
		assign_texture(&game->textures.east, line + 3);
	else if (line[0] == 'F' && line[1] == ' ')
		assign_color(&game->colors, line + 2, TRUE);
	else if (line[0] == 'C' && line[1] == ' ')
		assign_color(&game->colors, line + 2, FALSE);
}
