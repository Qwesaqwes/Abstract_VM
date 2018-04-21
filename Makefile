# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/09 16:15:09 by jichen-m          #+#    #+#              #
#    Updated: 2018/04/21 22:03:01 by jichen-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = avm

CC = clang++

SRC = ./main.cpp

SRC1 = ./srcs/*.cpp

FLAGS = -Wall -Wextra -Werror

SRCO = $(SRC:.cpp=.o)
SRC1O = $(SRC1:.cpp=.o)

all: $(NAME)

$(NAME) :
		@$(CC) $(FLAGS) -c $(SRC) $(SRC1)
		@$(CC) -o $(NAME) $(SRCO)

clean:
		@rm -rf ./*.o
		@echo "objects files have been removed ! ✓"

fclean: clean
		@rm -rf $(NAME)
		@echo "$(NAME) has been removed ! ✓"

re: fclean all

.PHONY	:		all clean re
