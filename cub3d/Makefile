# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/12 22:37:10 by rzt               #+#    #+#              #
#    Updated: 2025/11/20 12:55:42 by rzamolo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
RM			= rm -rf
INCLUDE_DIR = ./include
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a
LIBFT_FLAGS	= -L$(LIBFT_DIR) -lft
MLX_DIR		= ./mlx
MLX			= $(MLX_DIR)/libmlx42.a
MLX_FLAGS	= -L$(MLX_DIR) -lmlx42 -ldl -lglfw -pthread 
LDFLAGS		= -lm

SRC_DIR		= ./src

OBJ_DIR		= obj

SRC_FILES	= \
	$(SRC_DIR)/cub3d.c \
	$(SRC_DIR)/engine/dda_algo.c \
	$(SRC_DIR)/engine/minimap.c \
	$(SRC_DIR)/engine/raycasting.c \
	$(SRC_DIR)/events/handle_keys.c \
	$(SRC_DIR)/events/handle_mouse.c \
	$(SRC_DIR)/events/player_movement.c \
	$(SRC_DIR)/frees/free.c \
	$(SRC_DIR)/inits/game.c \
	$(SRC_DIR)/inits/setting_textures.c \
	$(SRC_DIR)/inits/player.c \
	$(SRC_DIR)/inits/settings.c \
	$(SRC_DIR)/inits/textures.c \
	$(SRC_DIR)/parsing/parse_colors.c \
	$(SRC_DIR)/parsing/parse_field_line.c \
	$(SRC_DIR)/parsing/parse_file.c \
	$(SRC_DIR)/parsing/parse_map_1.c \
	$(SRC_DIR)/parsing/parse_map_3.c \
	$(SRC_DIR)/parsing/parse_map_2.c \
	$(SRC_DIR)/utils/ft_append_line.c \
	$(SRC_DIR)/utils/ft_free_split.c \
	$(SRC_DIR)/utils/ft_isspace.c \
	$(SRC_DIR)/validations/extension.c \
	$(SRC_DIR)/validations/map_check.c \
	$(SRC_DIR)/validations/tex_extension.c
# 	$(SRC_DIR)/events/player_movement.c



OBJS        = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "Linking Cub3d..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) $(MLX_FLAGS) $(LDFLAGS) -o $(NAME)
	@echo "Cub3d compilation completed!"

$(LIBFT):
	@echo "Compiling Libft..."
	@$(MAKE) -s -C $(LIBFT_DIR)
	@echo "Libft compilation completed!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT)
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean

re: fclean all

norm:
	@norminette include/*
	@echo "\n"
	@norminette src/*

keycap:
	@cc src/mlx42_test.c mlx/libmlx42.a $(MLX_FLAGS) -o keycapture

run:	re
	@XDG_SESSION_TYPE=x11 ./$(NAME) assets/maps/cheese_maze.cub
	@XDG_SESSION_TYPE=x11 ./$(NAME) assets/maps/creepy.cub
	@XDG_SESSION_TYPE=x11 ./$(NAME) assets/maps/dungeon.cub
	@XDG_SESSION_TYPE=x11 ./$(NAME) assets/maps/library.cub
	@XDG_SESSION_TYPE=x11 ./$(NAME) assets/maps/sad_face.cub
	@XDG_SESSION_TYPE=x11 ./$(NAME) assets/maps/sample_map.cub

.PHONY: all clean fclean re

# The command below is used to generate the file `compile_commands.json` to clangd extension
# (yay -S bear). And can follow link to function definition or declaration

# bear -- make clean all

# Force X11 instead of Wayland (before run ./cub3d)
# export XDG_SESSION_TYPE=x11

# The sample_map is not working properly

# valgrind --leak-check=full --track-origins=yes ./cub3d maps/test.cub