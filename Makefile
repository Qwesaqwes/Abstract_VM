# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/09 16:15:09 by jichen-m          #+#    #+#              #
#    Updated: 2018/04/27 18:28:14 by jichen-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = avm

CC = clang++

SRC = ./main.cpp\
		$(wildcard ./srcs/*.cpp)

FLAGS = -Wall -Wextra -Werror

ODIR = ./BinaryFiles

SRCO = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME) : $(SRCO)
		@$(CC) $(FLAGS) $(SRCO) -o $(NAME)
		@mkdir $(ODIR)
		@mv $(SRCO) $(ODIR)

%.o: %.cpp
		@$(CC) $(FLAGS) -o $@ -c $<
clean:
		@rm -rf $(ODIR)
		@echo "objects files have been removed ! ✓"

fclean: clean
		@rm -rf $(NAME)
		@echo "$(NAME) has been removed ! ✓"

re: fclean all

.PHONY	:		all clean re
