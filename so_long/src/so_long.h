/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

# define TILE_SIZE 50

typedef struct s_point
{
	int	y;
	int	x;
}	t_point;

typedef struct s_counts
{
	int	p_count;
	int	e_count;
	int	c_count;
}	t_counts;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	size_t	rows;
	size_t	cols;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
	int		on_exit;
	int		collectibles;
	int		moves;
	void	*wall;
	void	*player;
	void	*collectible;
	void	*exit;
	void	*exit2;
	void	*floor;
	void	*player_up[4];
	void	*player_down[4];
	void	*player_left[4];
	void	*player_right[4];
	int		current_frame;
	int		direction;
	int		fd;
}	t_game;

typedef struct s_flood_fill_data
{
	char	**map;
	int		rows;
	int		cols;
	int		*c_count;
	int		*e_reached;
}	t_flood_fill_data;

void	load_map(t_game *game, const char *filename);
void	validate_map(t_game *game);
void	check_valid_path(t_game *game);
void	init_game(t_game *game);
void	load_textures(t_game *game, int tile_size);
void	move_player(t_game *game, int dx, int dy);
int		check_win(t_game *game);
void	free_map(t_game *game);
void	load_player_animation(t_game *game);
void	render_map(t_game *game);
int		handle_keypress(int keycode, t_game *game);
int		close_game(t_game *game);
void	error_exit(const char *msg);
void	validate_character(t_game *game, char c);
void	validate_borders(t_game *game, char c, size_t y, size_t x);
void	validate_map_characters(t_game *game, t_counts *counts);
void	validate_map_counts(t_game *game, t_counts *counts);
void	render_tile(t_game *game, size_t y, size_t x);
void	free_temp_map(char **temp_map, size_t rows);
void	count_player(t_game *game, t_point coords, t_counts *counts);
void	count_exit(t_game *game, t_point coords, t_counts *counts);
void	count_elements(t_game *game, char c, t_point coords, t_counts *counts);

#endif
