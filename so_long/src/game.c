#include "so_long.h"

void init_game(t_game *game) {
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, game->cols * TILE_SIZE, game->rows * TILE_SIZE, "so_long");
    int tile_size = TILE_SIZE;
    load_player_animation(game);
    game->on_exit = 0;

    game->wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", &tile_size, &tile_size);
    game->player = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm", &tile_size, &tile_size);
    game->collectible = mlx_xpm_file_to_image(game->mlx, "textures/collectible.xpm", &tile_size, &tile_size);
    game->exit = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm", &tile_size, &tile_size);
    game->floor = mlx_xpm_file_to_image(game->mlx, "textures/tile1.xpm", &tile_size, &tile_size);

    if (!game->wall) printf("Error: No se pudo cargar wall.xpm\n");
    if (!game->player) printf("Error: No se pudo cargar player.xpm\n");
    if (!game->collectible) printf("Error: No se pudo cargar collectible.xpm\n");
    if (!game->exit) printf("Error: No se pudo cargar exit.xpm\n");

    if (!game->wall || !game->player || !game->collectible || !game->exit) {
        error_exit("Error: No se pudieron cargar las texturas.");
    }

    render_map(game);
}

void load_player_animation(t_game *game) {
    int tile_size = TILE_SIZE;
    game->player_up[0] = mlx_xpm_file_to_image(game->mlx, "textures/player_up_1.xpm", &tile_size, &tile_size);
    game->player_up[1] = mlx_xpm_file_to_image(game->mlx, "textures/player_up_2.xpm", &tile_size, &tile_size);
    game->player_up[2] = mlx_xpm_file_to_image(game->mlx, "textures/player_up_3.xpm", &tile_size, &tile_size);
    game->player_up[3] = mlx_xpm_file_to_image(game->mlx, "textures/player_up_4.xpm", &tile_size, &tile_size);

    game->player_down[0] = mlx_xpm_file_to_image(game->mlx, "textures/player_down_1.xpm", &tile_size, &tile_size);
    game->player_down[1] = mlx_xpm_file_to_image(game->mlx, "textures/player_down_2.xpm", &tile_size, &tile_size);
    game->player_down[2] = mlx_xpm_file_to_image(game->mlx, "textures/player_down_3.xpm", &tile_size, &tile_size);
    game->player_down[3] = mlx_xpm_file_to_image(game->mlx, "textures/player_down_4.xpm", &tile_size, &tile_size);

    game->player_left[0] = mlx_xpm_file_to_image(game->mlx, "textures/player_left_1.xpm", &tile_size, &tile_size);
    game->player_left[1] = mlx_xpm_file_to_image(game->mlx, "textures/player_left_2.xpm", &tile_size, &tile_size);
    game->player_left[2] = mlx_xpm_file_to_image(game->mlx, "textures/player_left_3.xpm", &tile_size, &tile_size);
    game->player_left[3] = mlx_xpm_file_to_image(game->mlx, "textures/player_left_4.xpm", &tile_size, &tile_size);

    game->player_right[0] = mlx_xpm_file_to_image(game->mlx, "textures/player_right_1.xpm", &tile_size, &tile_size);
    game->player_right[1] = mlx_xpm_file_to_image(game->mlx, "textures/player_right_2.xpm", &tile_size, &tile_size);
    game->player_right[2] = mlx_xpm_file_to_image(game->mlx, "textures/player_right_3.xpm", &tile_size, &tile_size);
    game->player_right[3] = mlx_xpm_file_to_image(game->mlx, "textures/player_right_4.xpm", &tile_size, &tile_size);

    for (int i = 0; i < 4; i++) {
        if (!game->player_up[i] || !game->player_down[i] || !game->player_left[i] || !game->player_right[i]) {
            error_exit("Error: No se pudieron cargar las texturas de animación del jugador.");
        }
    }

    game->current_frame = 0;
    game->direction = 1; 
}

void move_player(t_game *game, int dx, int dy) {
    int new_x = game->player_x + dx;
    int new_y = game->player_y + dy;

    if (game->map[new_y][new_x] == '1') {
        return; 
    }

    if (game->map[new_y][new_x] == 'C') {
        game->collectibles--; 
    }

    if (game->map[new_y][new_x] == 'E' && game->collectibles == 0) {
        printf("¡Has ganado!\n");
        close_game(game);
    }

    if (game->on_exit) {
        game->map[game->player_y][game->player_x] = 'E'; 
    } else {
        game->map[game->player_y][game->player_x] = '0';
    }

    game->on_exit = (game->map[new_y][new_x] == 'E');
    game->player_x = new_x;
    game->player_y = new_y;
    game->map[new_y][new_x] = 'P';

    if (dy == -1) game->direction = 0; 
    else if (dy == 1) game->direction = 1; 
    else if (dx == -1) game->direction = 2;
    else if (dx == 1) game->direction = 3; 
    game->current_frame = (game->current_frame + 1) % 4;

    game->moves++;
    printf("Movimientos: %d\n", game->moves);

    render_map(game); 
}