NAME		= philo
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDE_DIR = ./include
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a
LIBFT_FLAGS	= -L$(LIBFT_DIR) -lft

SRC_DIR		= ./src
INIT_DIR	= $(SRC_DIR)/initialization
VAL_DIR		= $(SRC_DIR)/validation
UTILS_DIR	= $(SRC_DIR)/utils
PHILOS_DIR  = $(SRC_DIR)/philos

OBJ_DIR		= obj

SRC_FILES	= \
    $(SRC_DIR)/philo.c \
	$(VAL_DIR)/input_validation.c \
	$(PHILOS_DIR)/monitor_philos.c \
	$(PHILOS_DIR)/philos_act.c \
	$(UTILS_DIR)/utils.c \
	$(INIT_DIR)/init.c \


OBJS        = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re