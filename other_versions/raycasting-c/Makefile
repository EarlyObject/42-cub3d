# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/27 16:44:54 by asydykna          #+#    #+#              #
#    Updated: 2021/05/01 17:15:47 by asydykna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/*.c\
	

#OBJ = 

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

INCLUDES = ./includes

all: build

build:
	$(CC) $(SRC) -lSDL2 -o raycast;

debug:
	$(CC) -g $(SRC) -lSDL2;

run:
	./raycast;

clean:
	$(RM) raycast

#fclean: clean
#	$(RM) $(OBJ)

re: fclean all

.PHONY: all clean fclean re
