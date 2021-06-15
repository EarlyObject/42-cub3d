/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:01:08 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/15 14:54:18 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdint.h>
# include <stdbool.h>
# include "defs.h"
# include "../mlx/mlx.h"

# define TEXTURES	7

typedef struct s_mlx
{
	void			*mlx;
	void			*window;
	void			*img;
}	t_mlx;

typedef struct s_keys {
	bool			w;
	bool			s;
	bool			a;
	bool			d;
	bool			left;
	bool			right;
}	t_keys;

typedef struct s_image
{
	void			*img_ptr;
	uint32_t		*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				img_width;
	int				img_height;
}	t_image;

typedef struct s_wall
{
	double			rayDirX;
	double			rayDirY;
	int				side;
	int				stepX;
	int				stepY;
	double			perpWallDist;
	int				texNum;
	uint32_t		texX;
	double			step;
	double			texPos;
	double			wallX;
	double			sideDistX;
	double			sideDistY;
	double			deltaDistX;
	double			deltaDistY;
	int				lineHeight;
	int				drawStart;
	int				drawEnd;
	int				x;
	uint32_t		color;
	uint32_t		*walTextrBuf;
	double			*z_buffer;

}	t_wall;

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

typedef struct s_player
{
	float			posX;
	float			posY;
	float			dirX;
	float			dirY;
}	t_player;

typedef struct s_screen
{
	int				mapX;
	int				mapY;
	double			planeX;
	double			planeY;


	uint32_t		color;
}	t_screen;

typedef struct s_d_list {
	void			*content;
	int				len;
	struct s_d_list	*next;
	struct s_d_list	*previous;
}	t_d_list;

enum		e_errors {
	ERR_ARGC_MIN = -15,
	ERR_ARGC_MAX,
	ERR_MAP_VALIDITY,
	ERR_MAP_BAD_ARG,
	ERR_MAP_C,
	ERR_MAP_OPEN,
};

typedef struct s_checklist {
	int				no_txt;
	int				so_txt;
	int				ea_txt;
	int				we_txt;
	int				sprite_txt;
	int				res_width;
	int				res_height;
	int				floor_c;
	int				ceiling_c;
	int				m;
	int				player;

}	t_checklist;

typedef struct s_sprite {
	float			x;
	float			y;
	double			sprite_x;
	double			sprite_y;
	double			trnsf_x;
	double			trnsf_y;
	int				draw_start_x;
	int				draw_start_y;
	int				draw_end_x;
	int				draw_end_y;
	int				spr_scr_x;
	int				spr_h;
	int				spr_w;
	int				tex_x;
	int				tex_y;
	uint32_t		color;
	uint32_t		*txtr_buf;
	double			*dist;
	double			**buf;
	double			*order;
}	t_sprite;

typedef struct s_config
{
	int				width;
	int				height;
	char			*map;
	bool			f_color_parse;
	bool			c_color_parse;
	int				floor_rgb[3];
	int				ceiling_rgb[3];
	int				rows;
	int				columns;
	int				num_sprites;
	char			*tex_path[TEXTURES];
	t_image			*wallTexture[TEXTURES];
	uint32_t		color[TEXTURES];
	size_t			max_len;
	char			player_direction;
	t_sprite		*sprites;
	int				hit;
}	t_config;

typedef struct s_cub3d
{
	void			*win;
	t_image			image;
	t_player		plr;
	t_mlx			mlx;
	t_wall			wall;
	t_screen		screen;
	t_config		*config;
	t_sprite		spr_data;
	t_d_list		*head;
	t_d_list		*lst;
	t_d_list		*tmp;
	char			*filename;
	t_checklist		checklist;
	int				get_res_w;
	int				get_res_h;
	t_keys			keys;
}	t_cub3d;

#endif