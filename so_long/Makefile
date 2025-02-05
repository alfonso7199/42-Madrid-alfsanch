NAME	=	libftprintf.a

SRCS	= \
		ft_printf.c\
		ft_convert_char.c\
		ft_convert_string.c\
		ft_convert_pointer.c\
		ft_convert_decimal.c\
		ft_convert_hexa.c\
		ft_convert_percentage.c\
		ft_convert_unsigned.c
		
OBJS	=	$(SRCS:.c=.o)

CC	=	gcc 

RM	=	rm -rf

AR	=	ar rcs

CFLAGS	=	-Wall -Wextra -Werror

INCLUDES = -I/usr/include -Imlx

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			$(AR) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

.PHONY	:	all clean fclean re

re	:	fclean all