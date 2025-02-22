/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	process_point(t_flood_fill_data *data, t_point p)
{
	int	y;
	int	x;

	y = p.y;
	x = p.x;
	if (data->map[y][x] == 'C')
		(*data->c_count)--;
	if (data->map[y][x] == 'E')
		*data->e_reached = 1;
	data->map[y][x] = 'V';
}

static void	flood_fill_loop(t_flood_fill_data *data, t_point *stack, int *top)
{
	t_point	p;

	while (*top > 0)
	{
		p = stack[--(*top)];
		if (p.y < 0 || p.y >= data->rows || p.x < 0 || p.x >= data->cols)
			continue ;
		if (data->map[p.y][p.x] == '1' || data->map[p.y][p.x] == 'V')
			continue ;
		process_point(data, p);
		stack[(*top)++] = (t_point){p.y + 1, p.x};
		stack[(*top)++] = (t_point){p.y - 1, p.x};
		stack[(*top)++] = (t_point){p.y, p.x + 1};
		stack[(*top)++] = (t_point){p.y, p.x - 1};
	}
}

void	flood_fill(t_flood_fill_data *data, int start_y, int start_x)
{
	t_point	*stack;
	int		top;

	stack = malloc(sizeof(t_point) * (data->rows * data->cols));
	if (!stack)
		error_exit("Error: Failed to allocate memory for flood fill");
	top = 0;
	stack[top++] = (t_point){start_y, start_x};
	flood_fill_loop(data, stack, &top);
	free(stack);
}

static void	init_temp_map(t_game *game, char ***temp_map)
{
	size_t	i;

	*temp_map = malloc(sizeof(char *) * game->rows);
	if (!*temp_map)
		error_exit("Error: Failed to allocate memory for temp map");
	i = 0;
	while (i < game->rows)
	{
		(*temp_map)[i] = ft_strdup(game->map[i]);
		i++;
	}
}

void	check_valid_path(t_game *game)
{
	int					c_count;
	int					e_reached;
	char				**temp_map;
	t_flood_fill_data	data;

	c_count = game->collectibles;
	e_reached = 0;
	init_temp_map(game, &temp_map);
	data.map = temp_map;
	data.rows = game->rows;
	data.cols = game->cols;
	data.c_count = &c_count;
	data.e_reached = &e_reached;
	flood_fill(&data, game->player_y, game->player_x);
	free_temp_map(temp_map, game->rows);
	if (c_count > 0 || e_reached == 0)
	{
		free_map(game);
		error_exit("Error: No valid path to complete the game");
	}
}
