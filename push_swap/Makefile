NAME		= push_swap
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDE_DIR = ./include
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a
LIBFT_FLAGS	= -L$(LIBFT_DIR) -lft

SRC_DIR		= ./src
INIT_DIR	= $(SRC_DIR)/initialization
VAL_DIR		= $(SRC_DIR)/validation
OP_DIR		= $(SRC_DIR)/operations
SORT_DIR	= $(SRC_DIR)/sorting
UTILS_DIR	= $(SRC_DIR)/utils

OBJ_DIR		= obj

SRC_FILES	= \
    $(SRC_DIR)/push_swap.c \
	$(INIT_DIR)/stack_initialization.c \
	$(INIT_DIR)/index_management.c \
	$(VAL_DIR)/input_validation.c \
	$(OP_DIR)/push.c \
	$(OP_DIR)/rotate.c \
	$(OP_DIR)/reverse_rotate.c \
	$(OP_DIR)/swap.c \
	$(SORT_DIR)/sort.c \
	$(SORT_DIR)/small_sort.c \
	$(UTILS_DIR)/sort_utils.c \
	$(SORT_DIR)/sort_large.c \
	$(UTILS_DIR)/stack_utils.c \
	$(UTILS_DIR)/error_utils.c \
	$(UTILS_DIR)/memory_utils.c

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