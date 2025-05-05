NAME		= philo
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDE_DIR = ./include

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
	$(UTILS_DIR)/ft_atoi.c \
	$(INIT_DIR)/init.c \


OBJS        = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re