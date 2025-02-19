#include "so_long.h"

void render_map(t_game *game) {
    mlx_clear_window(game->mlx, game->win);

    for (size_t y = 0; y < game->rows; y++) {
        for (size_t x = 0; x < game->cols; x++) {
            mlx_put_image_to_window(game->mlx, game->win, game->floor, x * TILE_SIZE, y * TILE_SIZE);
        }
    }

    for (size_t y = 0; y < game->rows; y++) {
        for (size_t x = 0; x < game->cols; x++) {
            if (game->map[y][x] == '1') {
                mlx_put_image_to_window(game->mlx, game->win, game->wall, x * TILE_SIZE, y * TILE_SIZE);
            } else if (game->map[y][x] == 'C') {
                mlx_put_image_to_window(game->mlx, game->win, game->collectible, x * TILE_SIZE, y * TILE_SIZE);
            } else if (game->map[y][x] == 'E') {
                mlx_put_image_to_window(game->mlx, game->win, game->exit, x * TILE_SIZE, y * TILE_SIZE);
            } else if (game->map[y][x] == 'P') {
                void *player_sprite = NULL;
                if (game->direction == 0) { 
                    player_sprite = game->player_up[game->current_frame];
                } else if (game->direction == 1) { 
                    player_sprite = game->player_down[game->current_frame];
                } else if (game->direction == 2) { 
                    player_sprite = game->player_left[game->current_frame];
                } else if (game->direction == 3) { 
                    player_sprite = game->player_right[game->current_frame];
                }
                mlx_put_image_to_window(game->mlx, game->win, player_sprite, x * TILE_SIZE, y * TILE_SIZE);
            }
        }
    }
}