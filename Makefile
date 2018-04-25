# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jichen-m <jichen-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/09 16:15:09 by jichen-m          #+#    #+#              #
#    Updated: 2018/04/25 16:49:29 by jichen-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = avm

CC = clang++

SRC = $(wildcard ./*.cpp)\
		$(wildcard ./srcs/*.cpp)

FLAGS = -Wall -Wextra -Werror

SRCO = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME) :
		@$(CC) $(FLAGS) -c $(SRC)
		@$(CC) -o $(NAME) *.o

clean:
		@rm -rf *.o
		@echo "objects files have been removed ! ✓"

fclean: clean
		@rm -rf $(NAME)
		@echo "$(NAME) has been removed ! ✓"

re: fclean all

.PHONY	:		all clean re

#
# NAME =				avm
#
# CC =				clang++
#
# FLAGS =				-Wall -Werror -Wextra -g
#
# HEADERS =			-I ./
#
# SRC_DIR =			./
#
# COMPILED_DIR_NAME =	compiled
# COMPILED_DIR =		./$(COMPILED_DIR_NAME)/
#
# FILENAMES =			main Calculus Factory Parse
#
# COMPILED_PATHS :=	$(addsuffix .o,$(FILENAMES))
# COMPILED_PATHS :=	$(addprefix $(COMPILED_DIR),$(COMPILED_PATHS))
#
# all: $(NAME)
#
# $(NAME): $(COMPILED_PATHS)
# 	$(CC) -o $(NAME) $(FLAGS) $(HEADERS) $(COMPILED_PATHS)
#
# $(COMPILED_PATHS): $(COMPILED_DIR)%.o: $(SRC_DIR)%.cpp
# 	@/bin/mkdir -p $(COMPILED_DIR)
# 	$(CC) -c $(FLAGS) $(HEADERS) $< -o $@
#
# clean:
# 	-/bin/rm -f $(COMPILED_PATHS)
# 	/usr/bin/find . -name "$(COMPILED_DIR_NAME)" -maxdepth 1 -type d -empty -delete
#
# fclean: clean
# 	-/bin/rm -f $(NAME)
#
# re: fclean all
