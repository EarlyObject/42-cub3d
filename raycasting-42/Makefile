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

SRC = src/main.c src/graphics.c src/errors.c src/draw.c src/inits.c \
		src/textures.c src/ceiling.c src/sprite.c src/setups.c src/parse.c \
		src/params_parse.c gnl/get_next_line.c gnl/get_next_line_utils.c \
		src/screenshot.c src/map_parse.c src/utils_parse.c src/str_parse.c \
		src/key_management.c src/player.c


# src/map.c  src/ray.c \
      src/utils.c src/wall.c  src/draw_sprites.c \
          \
        \
          src/window.c \
      src/ray_utils.c src/ray_calculations.c src/memory_mngt.c
OBJ = $(SRC:.c=.o)

NAME = cub3D

#LIBFT_LINUX_PATH = libft
#LIBFT_LINUX_NAME = libft.a
MLX_PATH_LINUX = mlx_linux
MLX_LINUX_LINK = -lSDL2 -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

LIBFT_PATH = libft
LIBFT_NAME = libft.a
MLX_PATH = mlx
MLX_NAME = libmlx.a
MLX_LINK = -lSDL2 -Lmlx -lmlx -framework OpenGL -framework AppKit $(MLX_PATH)/$(MLX_NAME)

CC = gcc
CFLAGS = -Wall  -Werror -Wextra
RM = rm -f

$(NAME): $(MLX_NAME) $(OBJ)
	$(CC) -o $(NAME) $(OBJ)  $(MLX_LINK) $(MLX_PATH)/$(MLX_NAME) 
# -lSDL2

#$(LIBFT_LINUX_NAME):
	#$(MAKE) -C $(LIBFT_LINUX_PATH)

$(LIBFT_NAME):
	$(MAKE) -C $(LIBFT_PATH)

$(MLX_NAME):
	$(MAKE) -C $(MLX_PATH)

$(MLX_NAME_LINUX):
	$(MAKE) -C $(MLX_PATH_LINUX)

all: $(LIBFT_NAME) $(MLX_NAME) $(OBJ)
	gcc $(CFLAGS) $(SRC) $(MLX_LINK) $(LIBFT_PATH)/$(LIBFT_NAME) -o $(NAME)

debug: $(LIBFT_NAME) $(MLX_NAME) $(OBJ)
	gcc -fsanitize=address -g3 $(CFLAGS) $(SRC) $(MLX_LINK) $(LIBFT_PATH)/$(LIBFT_NAME) -o $(NAME)

linux: $(LIBFT_LINUX_NAME) $(MLX_NAME_LINUX) $(OBJ)
	gcc -fsanitize=address -g3 $(CFLAGS) $(SRC) $(LIBFT_LINUX_PATH)/$(LIBFT_LINUX_NAME) $(MLX_LINUX_LINK)

norminette:
	norminette $(SRC) $(LIBFT_PATH)

clean:
	$(RM) $(OBJ)

cleanMLX:
	$(MAKE) clean -C $(MLX_PATH)

cleanMLX_LINUX:
	$(MAKE) clean -C $(MLX_LINUX_PATH)

fclean: clean cleanMLX
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
