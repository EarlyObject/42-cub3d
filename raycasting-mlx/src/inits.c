/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 08:34:45 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/27 20:18:44 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	init_player(t_cub3d *cub3d)
{
	cub3d->plr.x = cub3d->config->width / 2;
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
	cub3d->plr.moveSide = 0;
}

void
	init_config_arrays(t_config *config)
{
	int	i;

	i = 0;
	while (i < TEXTURES)
		config->tex_path[i++] = NULL;
	config->color[TEX_NORTH] = 0xFFFFFF;
	config->color[TEX_SOUTH] = 0xCCCCCC;
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
	config->visibleSprites = (t_sprite *)malloc(
			sizeof(t_sprite)* config->num_sprites);
}

void
	init_config(t_config *config)
{
	config->width = 848;
	config->height = 480;
	config->map = NULL;
	config->fov_angle = (60 * (PI / 180));
	config->frame_time_length = 1000 / FPS;
	config->rows = 0;
	config->columns = 0;
	config->save_arg = 0;
	config->dist_proj_plane = (
			(config->width / 2) / tan(config->fov_angle / 2));
	config->direction = 0;
	init_config_arrays(config);
}

void
	init_cub3d(t_cub3d *cub3d)
{
	t_image		image;
	t_player	player;
	t_wall		wall;
	t_rectangle	rectangle;
	t_line		line;

	image = (t_image){.img_ptr = NULL, .addr = NULL};
	player = (t_player){.x = 0, .y = 0};
	wall = (t_wall){.wallHeight = 0, .wallBottomY = 0,
		.wallTopY = 0, .textureOffsetX = 0, .textureOffsetY = 0};
	rectangle = (t_rectangle){.x = 0, .y = 0};
	line = (t_line){.x0 = 0, .y0 = 0};
	cub3d->win = NULL;
	cub3d->image = image;
	cub3d->plr = player;
	cub3d->wall = wall;
	cub3d->rectangle = rectangle;
	cub3d->line = line;
	cub3d->config = NULL;
	cub3d->rays = NULL;
}
