/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:34:26 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/11/20 12:38:12 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

static void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	update_movement(game);
	render_frame(game);
	close_game(game);
}

void	check_parse(t_game game)
{
	printf("North: %s\n", game.textures.north);
	printf("South: %s\n", game.textures.south);
	printf("East: %s\n", game.textures.east);
	printf("West: %s\n", game.textures.west);
	printf("Floor Color:\t R -> %d | G -> %d | B -> %d\n",
		game.colors.floor_r,
		game.colors.floor_g,
		game.colors.floor_b);
	printf("Ceiling Color:\t R -> %d | G -> %d | B -> %d\n",
		game.colors.ceiling_r,
		game.colors.ceiling_g,
		game.colors.ceiling_b);
	printf("Map Grid:\t Width -> %d | Height -> %d\n",
		game.map.width,
		game.map.height);
}

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc != 2)
		return (ft_putendl_fd("Error: invalid argumets!", 2), EXIT_FAILURE);
	if (!validate_map_extension(argv[1]))
		return (EXIT_FAILURE);
	set_mlx_settings();
	ft_bzero(&game, sizeof(t_game));
	game.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, GAME_NAME, FALSE);
	if (!game.mlx)
		return (ft_error(), EXIT_FAILURE);
	game.img = mlx_new_image(game.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game.img || (mlx_image_to_window(game.mlx, game.img, 0, 0) < 0))
		return (ft_error(), EXIT_FAILURE);
	open_file(&game, argv[1]);
	validate_texture_paths(&game.textures);
	mlx_set_cursor_mode(game.mlx, MLX_MOUSE_HIDDEN);
	load_textures(&game);
	mlx_cursor_hook(game.mlx, &handle_mouse, &game);
	mlx_key_hook(game.mlx, &key_event, &game);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_loop(game.mlx);
	ft_free(&game);
	return (EXIT_SUCCESS);
}
