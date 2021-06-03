/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 08:34:45 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/04 15:22:24 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	init_player(t_cub3d *cub3d)
{
	if (cub3d->config->direction == 'S')
	{
		cub3d->plr.dirX = 0;
		cub3d->plr.dirY = 1;
		cub3d->screen.planeX = 0.66;
		cub3d->screen.planeY = 0;
	}
	else if (cub3d->config->direction == 'N')
	{
		cub3d->plr.dirX = 0;
		cub3d->plr.dirY = -1;
		cub3d->screen.planeX = -0.66;
		cub3d->screen.planeY = 0;
	}
	else if (cub3d->config->direction == 'E')
	{
		cub3d->plr.dirX = -1;
		cub3d->plr.dirY = 0;
		cub3d->screen.planeX = 0;
		cub3d->screen.planeY = 0.66;
	}
	else if (cub3d->config->direction == 'W')
	{
		cub3d->plr.dirX = 1;
		cub3d->plr.dirY = 0;
		cub3d->screen.planeX = 0;
		cub3d->screen.planeY = -0.66;
	}
	cub3d->plr.posX = 9;
	cub3d->plr.posY = 9;
	cub3d->plr.moveSpeed = 0.9;
	cub3d->plr.rotSpeed = 0.5;

	/*cub3d->plr.x = cub3d->config->width / 2;
	cub3d->plr.y = cub3d->config->height / 2;
	cub3d->plr.width = 1;
	cub3d->plr.height = 1;
	cub3d->plr.turnDrcn = 0;
	cub3d->plr.walkDrcn = 0;
	if (cub3d->config->direction == 'N')
		cub3d->plr.rotAngle = -PI / 2;
	else if (cub3d->config->direction == 'S')
		cub3d->plr.rotAngle = PI / 2;
	else if (cub3d->config->direction == 'W')
		cub3d->plr.rotAngle = PI;
	else
		cub3d->plr.rotAngle = TWO_PI;
	cub3d->plr.walkSpeed = 100;
	cub3d->plr.turnSpeed = 45 * (PI / 180);
	cub3d->plr.moveSide = 0;*/
}

void
	init_cub3d(t_cub3d *cub3d)
{
	t_image		image;
	t_player	player;
	t_sprite	spr_data;

	/*
	t_wall		wall;
	t_rectangle	rectangle;
	t_line		line;



	wall = (t_wall){.wallHeight = 0, .wallBottomY = 0,
			.wallTopY = 0, .textureOffsetX = 0, .textureOffsetY = 0};
	rectangle = (t_rectangle){.x = 0, .y = 0};
	line = (t_line){.x0 = 0, .y0 = 0};
	*/

	cub3d->win = NULL;
	image = (t_image){.img_ptr = NULL, .addr = NULL};
	player = (t_player){.posX = 0, .posY = 0};
	cub3d->plr = player;
	cub3d->image = image;
	cub3d->config = NULL;
	spr_data = (t_sprite){.x = 0, .y = 0, .txtr = 0, .dist = 0, .trnsf_x = 0,
		.trnsf_y = 0, .dr_st_x = 0, .dr_st_y = 0, .dr_end_x = 0, .dr_end_y = 0,
		.spr_scr_x = 0, .vMoveScreen = 0, .spr_h = 0, .spr_w = 0, 
		.txtr_buf = NULL, .color = 0};
	cub3d->sprt_data = spr_data;

	/*
	cub3d->wall = wall;
	cub3d->rectangle = rectangle;
	cub3d->line = line;

	cub3d->rays = NULL;*/
}

void
	init_config_arrays(t_config *config)
{
	int	i;

	i = 0;
	while (i < TEXTURES)
		config->tex_path[i++] = NULL;
	config->color[TEX_NORTH] = 0xCFE2F3;
	config->color[TEX_SOUTH] = 0xFF9900;
	config->color[TEX_WEST] = 0xFF44FF;
	config->color[TEX_EAST] = 0x44FF44;
	config->color[TEX_SKY] = 0x33C6E3;
	config->color[TEX_FLOOR] = 0xA0764C;
	i = 0;
	while (i < C_LAST)
		config->set[i++] = 0;
	i = 0;
	while (i < TEXTURES)
		config->wallTexture[i++] = NULL;
}

void
	init_config(t_config *config)
{
	config->width = 1280;
	config->height = 800;
	config->num_sprites = 0;
	config->map = NULL;
	config->rows = 0;
	config->columns = 0;
	config->direction = 0;
	config->save_arg = 0;
	init_config_arrays(config);
}

void
	init_wall(t_cub3d *cub3d)
{
	int	i;

	cub3d->wall.ZBuffer
		= (double *)malloc(sizeof(double) * cub3d->config->width);
	i = 0;
	while (i < cub3d->config->width)
	{
		cub3d->wall.ZBuffer[i] = 0;
		i++;
	}	
}

void
	resume_init_config(t_config *config)
{
	config->num_sprites = count_sprites(config);
	config->sprites = (t_sprite *)malloc(
			sizeof(t_sprite)* config->num_sprites);
}
