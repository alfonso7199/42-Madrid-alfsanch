/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:52:14 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/11/20 12:55:13 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_ray_dir(t_ray *ray, t_player *player, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir.x = player->dir.x + player->plane.x * camera_x;
	ray->dir.y = player->dir.y + player->plane.y * camera_x;
}

void	calculate_height(t_ray *ray)
{
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

void	draw_vertical_line(t_game *game, t_ray *ray, int x)
{
	int			y;
	float		dist;
	uint32_t	color;

	y = 0;
	while (y < ray->draw_start)
	{
		dist = (WIN_HEIGHT / 2.0f) / (WIN_HEIGHT / 2.0f - y);
		color = darker_color(game->colors.ceiling, dist / 6.0f);
		mlx_put_pixel(game->img, x, y, color);
		y++;
	}
	draw_textured_column(game, ray, x);
	y = ray->draw_end;
	while (++y < WIN_HEIGHT)
	{
		dist = (WIN_HEIGHT / 2.0f) / (y - WIN_HEIGHT / 2.0f);
		color = darker_color(game->colors.floor, dist / 6.0f);
		mlx_put_pixel(game->img, x, y, color);
	}
}

void	cast_rays(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		calculate_ray_dir(&ray, &game->player, x);
		dda(game, &ray);
		calculate_height(&ray);
		draw_vertical_line(game, &ray, x);
		x++;
	}
}

void	render_frame(t_game *game)
{
	if (!game->img)
		return ;
	cast_rays(game);
	render_minimap(game);
}
