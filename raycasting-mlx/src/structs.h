/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:01:08 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/14 14:01:09 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

# include <stdint.h>
# include <stdbool.h>
# include <SDL2/SDL.h>
# include "upng.h"
# include "defs.h"
# include "../mlx/mlx.h"

# define NUM_TEXTURES 13
//# define NUM_TEXTURES 8
# define NUM_SPRITES 6


typedef struct		s_mlx
{
	void			*mlx;
	void			*window;
	void			*img;
}					t_mlx;

typedef struct s_ray{
	float		rayAngle;
	float		wallHitX;
	float		wallHitY;
	float		distance;
	bool		wasHitVertical;
	int			texture;
} t_ray;

typedef struct s_sprite {
	float		x;
	float		y;
	float		distance;
	float		height;
	float 		width;
	float 		top_y;
	float		bottom_y;
	float		angle;
	float		left_x;
	float		right_x;
	bool		visible;
	int			texture;
	int			texture_offset_y;
	int			texture_offset_x;
} t_sprite;

typedef struct s_image
{
	void		*img_ptr;
	uint32_t	*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}	t_image;

typedef struct s_player
{
	float		x;
	float		y;
	float		width;
	float		height;
	int			turnDrcn; //-1 for left, +1 for right
	int			walkDrcn; //-1 for back, +1 for front
	float		rotAngle;
	float		walkSpeed;
	float		turnSpeed;
} t_player;

typedef  struct	s_wall
{
	float	wallHeight;
	int		wallTopY;
	int		wallBottomY;
	int		textureOffsetY;
	int		textureOffsetX;
}	t_wall;

typedef  struct	s_rectangle
{
	int			x;
	int 		y;
	int			width;
	int			height;
} t_rectangle;

typedef  struct	s_line
{
	int			x0;
	int 		y0;
	int			x1;
	int			y1;
	int			longestSideLength;
} t_line;

typedef	struct		s_cub3d
{
	void		*win;
	t_image		image;
	t_player	plr;
	t_mlx		mlx;
	t_image		*wallTexture[NUM_TEXTURES];
	t_wall 		wall;
	t_sprite 	*sprites[NUM_SPRITES];
	t_rectangle rectangle;
	t_line 		line;
}	t_cub3d;

#endif