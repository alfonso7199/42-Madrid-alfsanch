/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:01:41 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/11/12 14:16:39 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	**alloc_visited(t_map *map)
{
	int	**visited;
	int	y;

	y = 0;
	visited = malloc(sizeof(int *) * map->height);
	if (!visited)
		exit(EXIT_FAILURE);
	while (y < map->height)
	{
		visited[y] = ft_calloc(map->width, sizeof(int));
		if (!visited[y])
			exit(EXIT_FAILURE);
		y++;
	}
	return (visited);
}

static void	free_visited(int **visited, int height)
{
	int	y;

	y = 0;
	while (y < height)
	{
		free(visited[y]);
		y++;
	}
	free(visited);
}

static void	flood_fill(t_map *map, int x, int y, t_fillctx *ctx)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return ;
	if (ctx->visited[y][x])
		return ;
	if (map->grid[y][x] == '1')
		return ;
	ctx->visited[y][x] = 1;
	if (ft_strchr("0NSEW", map->grid[y][x]))
		ctx->leak = 1;
	flood_fill(map, x + 1, y, ctx);
	flood_fill(map, x - 1, y, ctx);
	flood_fill(map, x, y + 1, ctx);
	flood_fill(map, x, y - 1, ctx);
}

static void	check_borders(t_map *map, t_fillctx *ctx)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if ((y == 0 || y == map->height - 1
					|| x == 0 || x == map->width - 1)
				&& map->grid[y][x] != '1')
				flood_fill(map, x, y, ctx);
			x++;
		}
		y++;
	}
}

t_bool	is_map_closed(t_map *map)
{
	t_fillctx	ctx;

	ctx.visited = alloc_visited(map);
	ctx.leak = 0;
	check_borders(map, &ctx);
	free_visited(ctx.visited, map->height);
	return (!ctx.leak);
}
