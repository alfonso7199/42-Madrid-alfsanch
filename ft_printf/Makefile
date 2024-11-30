NAME	=	libftprintf.a

SRCS	= \
		ft_printf.c\
		ft_ft_convert_char.c\
		ft_ft_convert_string.c\
		ft_convert_pointer.c\
		ft_convert_decimal.c\
		ft_convert_xX.c\
		ft_convert_percentage.c\
		
OBJS	=	$(SRCS:.c=.o)

CC	=	gcc 

RM	=	rm -rf

AR	=	ar rcs

CFLAGS	=	-Wall -Wextra -Werror

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			$(AR) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

.PHONY	:	all clean fclean re

re	:	fclean all