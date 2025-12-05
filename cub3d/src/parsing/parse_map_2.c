/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:07:45 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/11/20 12:37:44 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	copy_original_chars(char *new_line, char *old_line, int curr_len)
{
	int	i;

	i = 0;
	while (i < curr_len)
	{
		new_line[i] = old_line[i];
		i++;
	}
}

static void	fill_with_spaces(char *new_line, int start, int target_width)
{
	int	i;

	i = start;
	while (i < target_width)
	{
		new_line[i] = ' ';
		i++;
	}
	new_line[target_width] = '\0';
}

static void	pad_line_to_width(char **line_ptr, int target_width)
{
	int		curr_len;
	char	*new_line;

	curr_len = (int)ft_strlen(*line_ptr);
	if (curr_len >= target_width)
		return ;
	new_line = (char *)malloc(target_width + 1);
	if (!new_line)
		exit (EXIT_FAILURE);
	copy_original_chars(new_line, *line_ptr, curr_len);
	fill_with_spaces(new_line, curr_len, target_width);
	free(*line_ptr);
	*line_ptr = new_line;
}

static void	compute_map_dimensions(t_map *map)
{
	int	row_idx;
	int	line_len;

	row_idx = 0;
	map->width = 0;
	map->height = 0;
	while (map->grid && map->grid[row_idx])
	{
		line_len = (int)ft_strlen(map->grid[row_idx]);
		if (line_len > map->width)
			map->width = line_len;
		map->height++;
		row_idx++;
	}
}

void	normalize_map_with_spaces(t_map *map)
{
	int	row;

	compute_map_dimensions(map);
	row = 0;
	while (row < map->height)
	{
		pad_line_to_width(&map->grid[row], map->width);
		row++;
	}
}
