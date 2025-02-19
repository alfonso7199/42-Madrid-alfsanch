#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

# define TILE_SIZE 50

typedef struct s_game {
    void    *mlx;
    void    *win;
    char    **map;
    size_t     rows;
    size_t     cols;
    int     player_x;
    int     player_y;
    int     exit_x;
    int     exit_y;
    int     on_exit;
    int     collectibles;
    int     moves;
    void    *wall;
    void    *player;
    void    *collectible;
    void    *exit;
    void    *floor;
    void    *player_up[4];
    void    *player_down[4];
    void    *player_left[4];
    void    *player_right[4];
    int     current_frame;
    int     direction;    
} t_game;

void    load_map(t_game *game, const char *filename);
void    validate_map(t_game *game);
void    check_valid_path(t_game *game);
void    init_game(t_game *game);
void    move_player(t_game *game, int dx, int dy);
int     check_win(t_game *game);
void    free_map(t_game *game);
void    load_player_animation(t_game *game);
void    render_map(t_game *game);

int     handle_keypress(int keycode, t_game *game);
int     close_game(t_game *game);

void    error_exit(const char *msg);

#endif