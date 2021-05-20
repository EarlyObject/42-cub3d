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
# include "defs.h"
# include "../mlx/mlx.h"

# define NUM_TEXTURES 13
//# define NUM_TEXTURES 8
# define NUM_SPRITES 3
# define TEXTURES			7
# define C_LAST				9

typedef struct	s_str
{
	char			*content;
	struct s_str	*next;
}				t_str;

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
	float		xintercept;
	float		yintercept;
	float		xstep;
	float		ystep;
	bool		foundHorzWallHit;
	float		horzWallHitX;
	float		horzWallHitY;
	int			horzWallTexture;
	bool		foundVertWallHit;
	float		vertWallHitX;
	float		vertWallHitY;
	int			vertWallTexture;
	float		nextVertTouchX;
	float		nextVertTouchY;
	float		nextHorzTouchX;
	float		nextHorzTouchY;
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
	int 		moveSide;
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

typedef struct	s_config
{
	int			width;
	int			height;
	int			*map;
	int			rows;
	int			columns;
	int			save_arg;
	float		dist_proj_plane;
	char 		direction;
	char		*tex_path[TEXTURES];
	uint32_t	c[TEXTURES];
	int			set[C_LAST];
	t_sprite 	*sprites[NUM_SPRITES];
}				t_config;

typedef struct		s_screenshot
{
	char			byte_type[2];
	uint32_t		byte_size;
	uint32_t		byte_reserved;
	uint32_t		byte_offset;
	uint32_t		header_size;
	uint32_t		image_width;
	uint32_t		image_height;
	unsigned short	color_planes;
	unsigned short	bpp;
	uint32_t		compression;
	uint32_t 		image_size;
	int				bits_xpels_per_meter;
	int				bits_ypels_per_meter;
	uint32_t		total_colors;
	uint32_t		important_colors;
}					t_screenshot;


typedef	struct		s_cub3d
{
	void		*win;
	t_image		image;
	t_player	plr;
	t_mlx		mlx;
	t_wall 		wall;
	t_rectangle rectangle;
	t_line 		line;
	t_config	*config;
	t_ray		*rays;
	t_image		*wallTexture[NUM_TEXTURES];
	t_sprite 	*sprites[NUM_SPRITES];
}					t_cub3d;

#endif