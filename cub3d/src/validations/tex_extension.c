/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_extension.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:29:46 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/11/18 18:39:59 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	has_png_extension(char *path)
{
	char	*dot;
	int		len;

	if (!path)
		return (FALSE);
	len = ft_strlen(path);
	if (len < 4)
		return (FALSE);
	dot = ft_strrchr(path, '.');
	if (!dot)
		return (FALSE);
	if (ft_strncmp(dot, ".png", 4) == 0)
		return (TRUE);
	return (FALSE);
}

static t_bool	file_exists(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (FALSE);
	close(fd);
	return (TRUE);
}

static void	validate_single_path(char *path, char *direction)
{
	if (!has_png_extension(path))
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putstr_fd(direction, STDERR_FILENO);
		ft_putendl_fd(" texture must be .png", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (!file_exists(path))
	{
		ft_putstr_fd("Error: texture file not found: ", STDERR_FILENO);
		ft_putendl_fd(path, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	validate_texture_paths(t_textures *textures)
{
	validate_single_path(textures->north, "North");
	validate_single_path(textures->south, "South");
	validate_single_path(textures->east, "East");
	validate_single_path(textures->west, "West");
}
