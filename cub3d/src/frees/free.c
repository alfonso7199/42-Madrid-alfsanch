/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:29:17 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/11/20 19:41:44 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures_path(t_textures *textures)
{
	if (textures->north)
		free(textures->north);
	if (textures->south)
		free(textures->south);
	if (textures->east)
		free(textures->east);
	if (textures->west)
		free(textures->west);
}

void	free_textures(t_game *game)
{
	if (game->tex_set.north)
		mlx_delete_texture(game->tex_set.north);
	if (game->tex_set.south)
		mlx_delete_texture(game->tex_set.south);
	if (game->tex_set.east)
		mlx_delete_texture(game->tex_set.east);
	if (game->tex_set.west)
		mlx_delete_texture(game->tex_set.west);
}

void	ft_free(t_game *game)
{
	if (!game)
		return ;
	free_textures_path(&game->textures);
	free_textures(game);
	if (game->map.grid)
		ft_free_split(game->map.grid);
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	if (game->mlx)
		mlx_terminate(game->mlx);
}
