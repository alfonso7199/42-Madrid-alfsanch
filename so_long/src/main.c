#include "so_long.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        error_exit("Uso: ./so_long mapa.ber");
    }

    t_game game = {0};
    load_map(&game, argv[1]);
    validate_map(&game);
    check_valid_path(&game);
    init_game(&game);

    mlx_key_hook(game.win, handle_keypress, &game);
    mlx_hook(game.win, 17, 0, close_game, &game);
    mlx_loop(game.mlx);

    return (0);
}