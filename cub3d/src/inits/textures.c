/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:45:01 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/11/20 19:41:12 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	exit_texture_error(char *path)
{
	ft_putstr_fd("Error: cannot load texture: ", STDERR_FILENO);
	ft_putendl_fd(path, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

static	mlx_texture_t	*load_single_texture(char *path)
{
	mlx_texture_t	*texture;

	if (!path)
		exit_texture_error("(null path)");
	texture = mlx_load_png(path);
	if (!texture)
		exit_texture_error(path);
	return (texture);
}

static void	init_texture_set(t_texture_set *tex_set)
{
	tex_set->north = NULL;
	tex_set->south = NULL;
	tex_set->east = NULL;
	tex_set->west = NULL;
}

void	load_textures(t_game *game)
{
	init_texture_set(&game->tex_set);
	game->tex_set.north = load_single_texture(game->textures.north);
	game->tex_set.south = load_single_texture(game->textures.south);
	game->tex_set.east = load_single_texture(game->textures.east);
	game->tex_set.west = load_single_texture(game->textures.west);
}
