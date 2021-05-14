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

//# define NUM_TEXTURES 13
# define NUM_TEXTURES 8

typedef struct		s_mlx
{
	void			*mlx;
	void			*window;
	void			*img;
}					t_mlx;

typedef struct {
	float	rayAngle;
	float	wallHitX;
	float	wallHitY;
	float	distance;
	bool	wasHitVertical;
	int		texture;
} ray_t;

typedef struct {
	float	x;
	float	y;
	float	distance;
	float	angle;
	bool	visible;
	int		texture;
} sprite_t;

typedef struct s_image
{
	void			*img_ptr;
	uint32_t		*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}	t_image;

typedef struct s_player
{
	float	x;
	float	y;
	float	width;
	float	height;
	int		turnDrcn; //-1 for left, +1 for right
	int		walkDrcn; //-1 for back, +1 for front
	float	rotAngle;
	float	walkSpeed;
	float	turnSpeed;
} t_player;

typedef  struct	s_texture
{
	int		textureWidth;
	int		textureHeight;
}	t_texture;

typedef  struct	s_wall
{
	float	wallHeight;
	int		wallTopY;
	int		wallBottomY;
	int		textureOffsetY;
	int		textureOffsetX;
}	t_wall;

typedef	struct		s_cub3d
{
	void		*win;
	t_image		image;
	t_player	plr;
	t_mlx		mlx;
	t_image		*wallTexture[NUM_TEXTURES];
	t_texture	texture;
	t_wall 		wall;
}	t_cub3d;

#endif