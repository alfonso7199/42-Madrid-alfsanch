#include "so_long.h"

#include "so_long.h"

int handle_keypress(int keycode, t_game *game) {
    if (keycode == 65307) {
        close_game(game);
    } else if (keycode == 119 || keycode == 65362) { 
        move_player(game, 0, -1);
    } else if (keycode == 115 || keycode == 65364) { 
        move_player(game, 0, 1);
    } else if (keycode == 97 || keycode == 65361) { 
        move_player(game, -1, 0);
    } else if (keycode == 100 || keycode == 65363) { 
        move_player(game, 1, 0);
    }
    return (0);
}

int close_game(t_game *game) {
    if (game->wall) mlx_destroy_image(game->mlx, game->wall);
    if (game->player) mlx_destroy_image(game->mlx, game->player);
    if (game->collectible) mlx_destroy_image(game->mlx, game->collectible);
    if (game->exit) mlx_destroy_image(game->mlx, game->exit);
    mlx_destroy_window(game->mlx, game->win);
    exit(0);
}