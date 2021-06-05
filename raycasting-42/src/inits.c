/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 08:34:45 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/05 15:29:48 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	init_ew_direction(t_cub3d *cub3d)
{
	if (cub3d->config->direction == 'E')
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
}

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
	else if (cub3d->config->direction == 'E' || cub3d->config->direction == 'W')
		init_ew_direction(cub3d);
	cub3d->plr.posX = 9;
	cub3d->plr.posY = 9;
	cub3d->plr.moveSpeed = 0.75;
	cub3d->plr.rotSpeed = 0.5;
}

void
	init_wall(t_cub3d *cub3d)
{
	int	i;

	cub3d->wall = (t_wall){.rayDirX = 0, .rayDirY = 0, .side = 0, .stepX = 0,
		.stepY = 0, .perpWallDist = 0, .texNum = 0, .texX = 0, .step = 0,
		.texPos = 0, .wallX = 0, .sideDistX = 0, .sideDistY = 0,
		.deltaDistX = 0, .deltaDistY = 0, .lineHeight = 0, .drawStart = 0,
		.drawEnd = 0, .color = 0, .walTextrBuf = 0};
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
	config->tile_width = config->width / config->columns;
	config->tile_height = config->height / config->rows;
}

void
	init_screen(t_cub3d *cub3d)
{
	t_screen	screen;

	screen = (t_screen){.mapX = 0, .mapY = 0, .planeX = 0, .planeY = 0,
		.rayDirX0 = 0, .rayDirY0 = 0, .rayDirX1 = 0, .rayDirY1 = 0, .floorX = 0,
		.floorY = 0, .floorStepX = 0, .floorStepY = 0, .color = 0,
		.walTextrBuf = NULL};
	cub3d->screen = screen;
}
