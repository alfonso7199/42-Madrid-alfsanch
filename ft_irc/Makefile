# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/10 17:29:29 by rzamolo-          #+#    #+#              #
#    Updated: 2026/04/24 19:43:10 by rzamolo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX					=	c++
CXXFLAGS			=	-Wall -Wextra -Werror -std=c++98
CXXFLAGS			+=	-Iincludes
DEPFLAGS			=	-MMD -MP

RM					=	rm -rf
NAME				=	ircserv
VALGRIND_LOG		=	valgrind.log

PORT				=	
PASSWD				=	

SRC_FILES			=	main.cpp Server.cpp Client.cpp Channel.cpp \
						commands/Cap.cpp commands/User.cpp \
						commands/Pass.cpp commands/Nick.cpp \
						commands/Join.cpp commands/Part.cpp commands/Privmsg.cpp \
						commands/Kick.cpp commands/Invite.cpp \
						commands/Topic.cpp commands/Mode.cpp \
						commands/Quit.cpp commands/Disconnect.cpp
SRC					=	$(addprefix sources/, $(SRC_FILES))
OBJ					=	$(SRC:.cpp=.o)
DEP					=	$(SRC:.cpp=.d)

all:				$(NAME)

$(NAME):			$(OBJ)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -o $@ $^

%.o:				%.cpp
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ) $(DEP)

fclean:				clean
	$(RM) $(NAME) $(VALGRIND_LOG) client

re:					fclean all


.PHONY:				all clean fclean re

-include $(DEP)

