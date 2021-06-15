# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/27 16:44:54 by asydykna          #+#    #+#              #
#    Updated: 2021/06/07 12:07:32 by asydykna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/main.c src/graphics.c src/errors.c src/inits.c src/textures.c \
		src/ceiling.c src/setups.c src/screenshot.c gnl/get_next_line.c \
		gnl/get_next_line_utils.c src/parse.c src/parse_two.c src/parse_three.c\
		src/parse_four.c src/parse_five.c src/parse_six.c src/parse_seven.c \
		src/parse_eight.c src/parse_nine.c src/parse_ten.c src/key_management.c\
		src/player.c src/wall.c src/wall_two.c src/sprite_calc.c \
		src/sprite_utils.c src/sprite.c

OBJ = $(SRC:.c=.o)

NAME = cub3D

LIBFT_PATH = libft
LIBFT_NAME = libft.a
MLX_PATH = mlx
MLX_NAME = libmlx.a
MLX_LINK = -Lmlx -lmlx -framework OpenGL -framework AppKit

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

$(NAME): $(OBJ)
	@$(MAKE) -C $(MLX_PATH)
	@$(MAKE) -C $(LIBFT_PATH)
	gcc $(CFLAGS) $(SRC) $(MLX_LINK) $(LIBFT_PATH)/$(LIBFT_NAME) -o $(NAME)

all: $(NAME)

norm:
	norminette $(SRC) $(LIBFT_PATH)

clean:
	$(RM) $(OBJ)
	$(MAKE) clean -C $(MLX_PATH)
	$(MAKE) clean -C $(LIBFT_PATH)

fclean: clean
	$(RM) $(NAME) $(MLX_NAME)
	$(MAKE) fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re norm
