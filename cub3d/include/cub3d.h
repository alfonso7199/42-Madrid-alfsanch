/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2025/11/20 19:42:18 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/MLX42.h"
# include <fcntl.h>		// open, 
# include <stdio.h>		// printf, perror
# include <stdlib.h>	// malloc, free, exit
# include <unistd.h>	// close, read, write
# include <string.h>	// strerror
# include <sys/time.h>	// gettimeofday
# include <X11/keysym.h> // KEYS
# include <math.h>

# define GREEN    "\033[32m"
# define RESET    "\033[0m"
# define RED      "\033[31m"

// MLX
# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define GAME_NAME "CUB3D"

// No se si es lento o rápido, habra que ver
# define MOVE_SPEED 0.02
# define ROT_SPEED 0.015
# define M_PI 3.14159265358979323846
# define MAX_SHADE_DIST 5.0f

// Minimap
# define MM_SCALE 5
# define MM_WALL_COLOR 0xFFFFFFFF
# define MM_FLOOR_COLOR 0x000000FF
# define MM_PLAYER_COLOR 0xFF0000FF

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef struct s_texture_set
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
}	t_texture_set;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_textures;

typedef struct s_colors
{
	int		floor;
	int		ceiling;
	int		floor_r;
	int		floor_g;
	int		floor_b;
	int		ceiling_r;
	int		ceiling_g;
	int		ceiling_b;
	t_bool	floor_set;
	t_bool	ceiling_set;
}	t_colors;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

//TODO: todas las structuras son básicas, es para hacernos una 
// idea inicial y luego ir viendo que más podemos necesitar
typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct s_player
{
	t_vec2	pos;
	t_vec2	dir;
	t_vec2	plane;
}	t_player;

typedef struct s_ray
{
	t_vec2	dir;
	t_vec2	side_dist;
	t_vec2	delta_dist;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_keys
{
	t_bool	w;
	t_bool	a;
	t_bool	s;
	t_bool	d;
	t_bool	left;
	t_bool	right;
	t_bool	esc;
}	t_keys;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_textures		textures;
	t_texture_set	tex_set;
	t_colors		colors;
	t_map			map;
	t_player		player;
	t_keys			keys;
}	t_game;

typedef struct s_fillctx
{
	int	**visited;
	int	leak;
}	t_fillctx;

// Init
void		set_mlx_settings(void);
t_game		*init_game(void);
void		init_player(t_game *game, int x, int y, char orientation);
void		set_dir_plane(t_player *player, char orientation);

// validations - extension
t_bool		validate_map_extension(const char *path);
t_bool		is_map_closed(t_map *map);

// Parsing
int			open_file(t_game *game, const char *path);
void		parse_map_line(t_game *game, char *line);
void		parse_field_line(t_game *game, char *line);
void		parse_color(t_colors *colors, char *line, t_bool is_floor);
void		normalize_map_with_spaces(t_map *map);
void		finalize_map(t_game *game);

// DDA
void		init_dda(t_ray *ray, t_player *player);
int			hit_wall(t_game *game, t_ray *ray);
void		dda_loop(t_ray *ray);
void		perpendicular_dist(t_ray *ray);
void		dda(t_game *game, t_ray *ray);

//Raycasting
void		render_frame(t_game *game);
void		cast_rays(t_game *game);
void		calculate_ray_dir(t_ray *ray, t_player *player, int x);
void		calculate_height(t_ray *ray);
void		draw_vertical_line(t_game *game, t_ray *ray, int x);
void		render_minimap(t_game *game);

// Movement
void		update_movement(t_game *game);
void		move_player(t_game *game, double move_x, double move_y);
void		rotate_player(t_game *game, double rot_speed);
t_bool		is_wall(t_game *game, int x, int y);
void		handle_mouse(double xpos, double ypos, void *param);

// Events
void		key_event(mlx_key_data_t keydata, void *param);
void		key_press(t_game *game, int key);
void		key_release(t_game *game, int key);
int			close_game(t_game *game);

// Textures
void		load_textures(t_game *game);
void		validate_texture_paths(t_textures *textures);
void		draw_textured_column(t_game *game, t_ray *ray, int x);
uint32_t	darker_color(uint32_t color, float factor);

// Free
void		ft_free(t_game *game);
void		free_textures(t_game *game);
void		free_textures_path(t_textures *textures);

// Utils
int			ft_isspace(int c);
char		**ft_append_line(char **old, char *new_line);
void		ft_free_split(char **split);

#endif
