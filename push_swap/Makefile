NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJ_DIR = obj
SRC_DIR = ./src
OPERATIONS_DIR = $(SRC_DIR)/operations
LIBFT_DIR = ./libft
INCLUDE = ./include

SRC =	$(SRC_DIR)/initialize.c $(SRC_DIR)/linked_list.c		\
		$(SRC_DIR)/miscellaneous.c $(SRC_DIR)/push_swap.c		\
		$(SRC_DIR)/push.c $(SRC_DIR)/r_rotate.c				\
		$(SRC_DIR)/rotate.c $(SRC_DIR)/sorting.c				\
		$(SRC_DIR)/swap.c $(SRC_DIR)/input_check.c			\
		$(SRC_DIR)/sort_util.c								\
		$(OPERATIONS_DIR)/pa.c $(OPERATIONS_DIR)/pb.c		\
		$(OPERATIONS_DIR)/ra.c $(OPERATIONS_DIR)/rb.c		\
		$(OPERATIONS_DIR)/rr.c $(OPERATIONS_DIR)/rra.c		\
		$(OPERATIONS_DIR)/rrb.c $(OPERATIONS_DIR)/rrr.c		\
		$(OPERATIONS_DIR)/sa.c $(OPERATIONS_DIR)/sb.c		\
		$(OPERATIONS_DIR)/ss.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

INCLUDE = -I$(INCLUDE_DIR) -I$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_FLAGS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/operations
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re