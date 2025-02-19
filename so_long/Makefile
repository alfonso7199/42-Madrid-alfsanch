NAME = so_long

SRCS = src/main.c src/map.c src/game.c src/render.c src/events.c src/utils.c
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = ./mlx
LIBFT_DIR = ./libft

INCLUDES = -I$(MLX_DIR) -I$(LIBFT_DIR) -I/usr/include

MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11 -lm -lz

LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(OBJS) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean 

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean 

re: fclean all

.PHONY: all clean fclean re
