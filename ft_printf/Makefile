NAME	=	libftprintf.a

SRCS	= \
		ft_printf.c\
		# ft_bzero.c\
		# ft_calloc.c\
		# ft_isalnum.c\
		# ft_isalpha.c\
		# ft_isascii.c\
		# ft_isdigit.c\
		# ft_isprint.c\
		# ft_toupper.c
		
OBJS	=	$(SRCS:.c=.o)

CC	=	gcc 

RM	=	rm -rf

CFLAGS	=	-Wall -Wextra -Werror

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			ar rcs $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)


.PHONY	:	all clean fclean re

re	:	fclean all