# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/27 16:44:54 by asydykna          #+#    #+#              #
#    Updated: 2021/05/06 13:27:13 by asydykna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SRC = src/*.c\

SRC = src/main.c src/graphics.c src/map.c src/player.c src/ray.c src/sprite.c \
	src/textures.c src/upng.c src/utils.c src/wall.c

OBJ = $(SRC:.c=.o)

NAME = raycast

MLX_PATH = minilibx
MLX_NAME = libmlx.a
MLX_LINK = -L$(MLX_PATH) -I includes -lmlx -framework OpenGL -framework AppKit

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

INCLUDES = ./includes

all: $(NAME)

$(NAME): $(MLX_NAME) $(OBJ) #build
	$(CC) -lSDL2 -o raycast $(OBJ) $(MLX_LINK) $(MLX_PATH)/$(MLX_NAME)

$(MLX_NAME):
	$(MAKE) -C $(MLX_PATH)

#build:
#	$(CC) $(SRC) -lSDL2 -o raycast $(OBJ) $(MLX_LINK $(MLX_PATH)/$(MLX_NAME);

debug:
	$(CC) -g $(SRC) -lSDL2;

run:
	./raycast;

clean:
	$(RM) $(OBJ)
	$(RM) $(NAME)

cleanMLX:
	$(MAKE) clean -C $(MLX_PATH)

fclean: clean cleanMLX
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
