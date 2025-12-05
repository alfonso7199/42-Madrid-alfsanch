/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:05:58 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/11/20 12:35:17 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_mouse(double xpos, double ypos, void *param)
{
	t_game	*game;
	double	delta_x;
	double	sensitivity;

	game = (t_game *)param;
	sensitivity = 0.001;
	(void)ypos;
	delta_x = xpos - (WIN_WIDTH / 2);
	rotate_player(game, delta_x * sensitivity);
	mlx_set_mouse_pos(game->mlx, WIN_WIDTH / 2, WIN_HEIGHT / 2);
}
