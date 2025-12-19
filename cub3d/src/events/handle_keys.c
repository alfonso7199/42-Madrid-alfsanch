/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2025/11/20 12:35:08 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_press(t_game *game, int key)
{
	if (key == MLX_KEY_ESCAPE)
		game->keys.esc = TRUE;
	if (key == MLX_KEY_W)
		game->keys.w = TRUE;
	if (key == MLX_KEY_S)
		game->keys.s = TRUE;
	if (key == MLX_KEY_A)
		game->keys.a = TRUE;
	if (key == MLX_KEY_D)
		game->keys.d = TRUE;
	if (key == MLX_KEY_LEFT)
		game->keys.left = TRUE;
	if (key == MLX_KEY_RIGHT)
		game->keys.right = TRUE;
}

void	key_release(t_game *game, int key)
{
	if (key == MLX_KEY_W)
		game->keys.w = FALSE;
	if (key == MLX_KEY_S)
		game->keys.s = FALSE;
	if (key == MLX_KEY_A)
		game->keys.a = FALSE;
	if (key == MLX_KEY_D)
		game->keys.d = FALSE;
	if (key == MLX_KEY_LEFT)
		game->keys.left = FALSE;
	if (key == MLX_KEY_RIGHT)
		game->keys.right = FALSE;
}

void	key_event(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		key_press(game, keydata.key);
		return ;
	}
	if (keydata.action == MLX_RELEASE)
	{
		key_release(game, keydata.key);
	}
}

int	close_game(t_game *game)
{
	if (game->keys.esc)
	{
		mlx_close_window(game->mlx);
		return (1);
	}
	return (0);
}
