#include "so_long.h"

void load_map(t_game *game, const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        error_exit("Error al abrir el archivo del mapa");
    }

    char *line;
    game->rows = 0;
    while ((line = get_next_line(fd))) {

        size_t len = ft_strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0'; 
        }
        char **new_map = realloc(game->map, (game->rows + 1) * sizeof(char *));
        if (!new_map) {
            close(fd);
            error_exit("Error: No se pudo asignar memoria para el mapa");
        }
        game->map = new_map;
        game->map[game->rows++] = line;
    }
    close(fd);

    if (game->rows == 0) {
        error_exit("Error: El mapa está vacío");
    }

    game->cols = ft_strlen(game->map[0]);
    for (size_t i = 1; i < game->rows; i++) {
        if (ft_strlen(game->map[i]) != game->cols) {
            error_exit("Error: El mapa no es rectangular");
        }
    }
}

void flood_fill(char **map, int y, int x, int rows, int cols, int *c_count, int *e_reached) {
    if (y < 0 || y >= rows || x < 0 || x >= cols || map[y][x] == '1' || map[y][x] == 'V') 
        return;

    if (map[y][x] == 'C') (*c_count)--;
    if (map[y][x] == 'E') (*e_reached) = 1;

    char temp = map[y][x];
    map[y][x] = 'V'; 

    flood_fill(map, y + 1, x, rows, cols, c_count, e_reached);
    flood_fill(map, y - 1, x, rows, cols, c_count, e_reached);
    flood_fill(map, y, x + 1, rows, cols, c_count, e_reached);
    flood_fill(map, y, x - 1, rows, cols, c_count, e_reached);

    map[y][x] = temp; 
}

void check_valid_path(t_game *game) {
    int c_count = game->collectibles;
    int e_reached = 0;

    char **temp_map = malloc(sizeof(char *) * game->rows);
    for (size_t i = 0; i < game->rows; i++) {
        temp_map[i] = ft_strdup(game->map[i]);
    }

    flood_fill(temp_map, game->player_y, game->player_x, game->rows, game->cols, &c_count, &e_reached);

    for (size_t i = 0; i < game->rows; i++) {
        free(temp_map[i]);
    }
    free(temp_map);

    if (c_count > 0 || e_reached == 0) {
        free_map(game);
        error_exit("Error: No hay un camino válido para completar el juego.");
    }
}

void validate_map(t_game *game) {
    int p_count = 0, e_count = 0, c_count = 0;

    for (size_t y = 0; y < game->rows; y++) {
        for (size_t x = 0; x < game->cols; x++) {
            char c = game->map[y][x];
            if (c != '0' && c != '1' && c != 'P' && c != 'E' && c != 'C') {
                free_map(game);
                error_exit("Error: Carácter inválido en el mapa");
            }

            if (y == 0 || y == game->rows - 1 || x == 0 || x == game->cols - 1) {
                if (c != '1') {
                    free_map(game);
                    error_exit("Error: Los bordes del mapa deben ser paredes ('1')");
                }
            }

            if (c == 'P') {
                game->player_x = x;
                game->player_y = y;
                p_count++;
            } else if (c == 'E') {
                game->exit_x = x;
                game->exit_y = y; 
                e_count++;
            } else if (c == 'C') {
                c_count++;
            }
        }
    }

    if (p_count != 1 || e_count != 1 || c_count < 1) {
        free_map(game);
        error_exit("Mapa inválido: debe tener 1 P, 1 E y al menos 1 C");
    }

    game->collectibles = c_count;
}
void free_map(t_game *game) {
    if (game->map) {
        for (size_t i = 0; i < game->rows; i++) {
            free(game->map[i]); 
        }
        free(game->map);
        game->map = NULL;
    }
}