/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:52:14 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/11/20 12:35:43 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//Calcula un rayo por columna por asi decirlo, por frame
//Por lo que igual toca bajar el número de frames maximo si vemos que va lento

void	init_dda(t_ray *ray, t_player *player)
{
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (player->pos.x - ray->map_x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = (ray->map_x + 1.0 - player->pos.x)
			* ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (player->pos.y - ray->map_y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = (ray->map_y + 1.0 - player->pos.y)
			* ray->delta_dist.y;
	}
}

int	hit_wall(t_game *game, t_ray *ray)
{
	if (ray->map_x < 0 || ray->map_x >= game->map.width)
		return (1);
	if (ray->map_y < 0 || ray->map_y >= game->map.height)
		return (1);
	if (game->map.grid[ray->map_y][ray->map_x] == '1')
		return (1);
	return (0);
}

void	dda_loop(t_ray *ray)
{
	if (ray->side_dist.x < ray->side_dist.y)
	{
		ray->side_dist.x += ray->delta_dist.x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist.y += ray->delta_dist.y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

void	perpendicular_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->perp_wall_dist = (ray->side_dist.y - ray->delta_dist.y);
}

void	dda(t_game *game, t_ray *ray)
{
	int	hit;

	ray->map_x = (int)game->player.pos.x;
	ray->map_y = (int)game->player.pos.y;
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
	init_dda(ray, &game->player);
	hit = 0;
	while (hit == 0)
	{
		dda_loop(ray);
		if (hit_wall(game, ray))
			hit = 1;
	}
	perpendicular_dist(ray);
}
