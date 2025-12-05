/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:31:06 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/11/20 12:36:09 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_north(t_player *player)
{
	player->dir.x = 0;
	player->dir.y = -1;
	player->plane.x = 0.66;
	player->plane.y = 0;
}

static void	set_south(t_player *player)
{
	player->dir.x = 0;
	player->dir.y = 1;
	player->plane.x = -0.66;
	player->plane.y = 0;
}

static void	set_west(t_player *player)
{
	player->dir.x = -1;
	player->dir.y = 0;
	player->plane.x = 0;
	player->plane.y = -0.66;
}

static void	set_east(t_player *player)
{
	player->dir.x = 1;
	player->dir.y = 0;
	player->plane.x = 0;
	player->plane.y = 0.66;
}

void	set_dir_plane(t_player *player, char orientation)
{
	if (orientation == 'N')
		set_north(player);
	else if (orientation == 'S')
		set_south(player);
	else if (orientation == 'W')
		set_west(player);
	else if (orientation == 'E')
		set_east(player);
	else
		ft_putendl_fd("Error: invalid player orientation", STDERR_FILENO);
}
