/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 17:29:14 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/11/20 12:36:14 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_texture_t	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x < 0)
			return (game->tex_set.east);
		return (game->tex_set.west);
	}
	if (ray->step_y < 0)
		return (game->tex_set.south);
	return (game->tex_set.north);
}

static int	get_tex_x(t_ray *ray, mlx_texture_t *tex, t_player *player)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = player->pos.y + ray->perp_wall_dist * ray->dir.y;
	else
		wall_x = player->pos.x + ray->perp_wall_dist * ray->dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->width);
	if ((ray->side == 0 && ray->dir.x > 0)
		|| (ray->side == 1 && ray->dir.y < 0))
		tex_x = tex->width - tex_x - 1;
	if (tex_x >= (int)tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}

static uint32_t	get_tex_color(mlx_texture_t *tex, int x, int y)
{
	int		idx;

	if (x < 0)
		x = 0;
	if (x >= (int)tex->width)
		x = tex->width - 1;
	if (y < 0)
		y = 0;
	if (y >= (int)tex->height)
		y = tex->height - 1;
	idx = (y * tex->width + x) * 4;
	return ((uint32_t)tex->pixels[idx + 0] << 24
		| (uint32_t)tex->pixels[idx + 1] << 16
		| (uint32_t)tex->pixels[idx + 2] << 8
		| (uint32_t)tex->pixels[idx + 3]);
}

void	draw_textured_column(t_game *game, t_ray *ray, int x)
{
	mlx_texture_t	*tex;
	int				tex_x;
	double			step;
	double			tex_pos;
	uint32_t		color;

	tex = get_wall_texture(game, ray);
	tex_x = get_tex_x(ray, tex, &game->player);
	step = 1.0 * tex->height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;
	while (ray->draw_start < ray->draw_end)
	{
		color = get_tex_color(tex, tex_x, (int)tex_pos % tex->height);
		color = darker_color(color, ray->perp_wall_dist / 10.0f);
		mlx_put_pixel(game->img, x, ray->draw_start, color);
		tex_pos += step;
		ray->draw_start++;
	}
}
