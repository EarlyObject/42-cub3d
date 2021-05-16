# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/27 16:44:54 by asydykna          #+#    #+#              #
#    Updated: 2021/05/16 17:59:58 by asydykna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/main.c src/graphics.c src/map.c src/player.c src/ray.c src/sprite.c \
	src/textures.c src/upng.c src/utils.c src/wall.c 

OBJ = $(SRC:.c=.o)

NAME = program

LIBFT_PATH = libft
LIBFT_NAME = libft.a
MLX_PATH = mlx
MLX_NAME = libmlx.a
MLX_LINK = -L$(MLX_PATH) -I includes -lmlx -framework OpenGL -framework AppKit

CC = gcc
CFLAGS = #-Wall  -Werror -Wextra
RM = rm -f

INCLUDES = ./includes

#all: $(NAME)

#$(MLX_LINK) $(MLX_PATH)/$(MLX_NAME)

#all: $(MLX_NAME) $(OBJ)
#	gcc -c -o program $(OBJ)  -Lmlx -I includes -lmlx -framework OpenGL -framework AppKit mlx/libmlx.a

all: $(LIBFT_NAME) $(MLX_NAME) $(OBJ)
	gcc   src/main.c src/graphics.c src/map.c src/player.c src/ray.c src/sprite.c \
        src/textures.c src/upng.c src/utils.c src/wall.c src/errors.c src/draw_sprites.c src/draw.c -o program -lSDL2 -Lmlx -lmlx -framework OpenGL -framework AppKit $(MLX_PATH)/$(MLX_NAME) $(LIBFT_PATH)/$(LIBFT_NAME)


$(NAME): $(MLX_NAME) $(OBJ)
	$(CC) -o $(NAME) $(OBJ)  $(MLX_LINK) $(MLX_PATH)/$(MLX_NAME) 
# -lSDL2

$(LIBFT_NAME):
	$(MAKE) -C $(LIBFT_PATH)

$(MLX_NAME):
	$(MAKE) -C $(MLX_PATH)

debug: $(LIBFT_NAME) $(MLX_NAME) $(OBJ)
	gcc -g src/main.c -g src/graphics.c -g src/map.c -g src/player.c -g src/ray.c -g src/sprite.c \
	-g src/textures.c -g src/upng.c -g src/utils.c -g src/wall.c src/errors.c src/draw_sprites.c src/draw.c -lSDL2 -o debugapp -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit $(LIBFT_PATH)/$(LIBFT_NAME)

clean:
	$(RM) $(OBJ)
	$(RM) $(NAME)

cleanMLX:
	$(MAKE) clean -C $(MLX_PATH)

fclean: clean cleanMLX
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
