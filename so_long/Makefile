NAME = so_long

SRC_DIR = src
OBJ_DIR = obj
MLX_DIR = ./mlx
LIBFT_DIR = ./libft

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/map_loading.c \
       $(SRC_DIR)/map_validation.c \
       $(SRC_DIR)/map_utils.c \
       $(SRC_DIR)/game_utils.c \
       $(SRC_DIR)/player_animation.c \
       $(SRC_DIR)/player_movement.c \
       $(SRC_DIR)/render_map.c \
	   $(SRC_DIR)/render_sprites.c \
       $(SRC_DIR)/events.c \
	   $(SRC_DIR)/free_map.c \
	   $(SRC_DIR)/count.c \
       $(SRC_DIR)/utils.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I$(MLX_DIR) -I$(LIBFT_DIR) -Iinclude
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11 -lm -lz
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(MLX_DIR)
	@$(CC) $(OBJS) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re