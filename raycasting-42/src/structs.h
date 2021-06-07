/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:01:08 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/07 10:17:42 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdint.h>
# include <stdbool.h>
# include "defs.h"
# include "../mlx/mlx.h"

# define TEXTURES	7
# define C_LAST		9

typedef struct s_str
{
	char			*content;
	struct s_str	*next;
}				t_str;

typedef struct s_mlx
{
	void			*mlx;
	void			*window;
	void			*img;
}					t_mlx;

typedef struct s_sprite {
	float		x;
	float		y;
	int			txtr;
	float		dist;
	double		trnsf_x;
	double		trnsf_y;
	int			dr_st_x;
	int			dr_st_y;
	int			dr_end_x;
	int			dr_end_y;
	int			spr_scr_x;
	int			vMoveScreen;
	int			spr_h;
	int			spr_w;
	int			tex_x;
	int			tex_y;
	uint32_t	color;
	uint32_t	*txtr_buf;
}	t_sprite;

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
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		rotSpeed;
	double		moveSpeed;
}	t_player;

typedef struct s_wall
{
	double		rayDirX;
	double		rayDirY;
	int			side;
	int			stepX;
	int			stepY;
	double		perpWallDist;
	int			texNum;
	int			texX;
	double		step;
	double		texPos;
	double		wallX;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
	uint32_t	color;
	uint32_t	*walTextrBuf;
	double		*ZBuffer;
}	t_wall;

typedef struct s_rectangle
{
	int			x;
	int			y;
	int			width;
	int			height;
}	t_rectangle;

typedef struct s_screenshot
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
	uint32_t		image_size;
	int				bits_xpels_per_meter;
	int				bits_ypels_per_meter;
	uint32_t		total_colors;
	uint32_t		important_colors;
}	t_screenshot;

typedef struct s_screen
{
	int			mapX;
	int			mapY;
	double		planeX;
	double		planeY;
	float		rayDirX0;
	float		rayDirY0;
	float		rayDirX1;
	float		rayDirY1;
	float		floorX;
	float		floorY;
	float		floorStepX;
	float		floorStepY;
	uint32_t	color;
	uint32_t	*walTextrBuf;
}	t_screen;

typedef struct s_config
{
	int			width;
	int			height;
	int			*map;
	int			rows;
	int			columns;
	int			num_sprites;
	int			tile_width;
	int			tile_height;
	char		direction;
	char		*tex_path[TEXTURES];
	t_image		*wallTexture[TEXTURES];
	uint32_t	color[TEXTURES];
	int			set[C_LAST];
	t_sprite	*sprites;
}	t_config;

typedef struct s_cub3d
{
	void		*win;
	t_image		image;
	t_player	plr;
	t_mlx		mlx;
	t_wall		wall;
	t_rectangle	rectangle;
	t_screen	screen;
	t_config	*config;
	t_sprite	sprt_data;
}	t_cub3d;

#endif