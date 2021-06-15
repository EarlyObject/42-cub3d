/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 08:34:45 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/15 18:22:33 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	init_keys(t_cub3d *cub3d)
{
	cub3d->keys.w = 0;
	cub3d->keys.a = 0;
	cub3d->keys.s = 0;
	cub3d->keys.d = 0;
	cub3d->keys.left = 0;
	cub3d->keys.right = 0;
}

void
	init_wall(t_cub3d *cub3d)
{
	cub3d->wall = (t_wall){.rayDirX = 0, .rayDirY = 0, .side = 0, .stepX = 0,
		.stepY = 0, .perpWallDist = 0, .texNum = 0, .texX = 0, .step = 0,
		.texPos = 0, .wallX = 0, .sideDistX = 0, .sideDistY = 0,
		.deltaDistX = 0, .deltaDistY = 0, .lineHeight = 0, .drawStart = 0,
		.drawEnd = 0, .color = 0, .walTextrBuf = 0};
}

void
	resume_init_config(t_cub3d *cub3d)
{
	int	i;

	cub3d->wall.z_buffer = (double *)malloc(sizeof(double)
			* cub3d->config->width);
	i = 0;
	while (i < cub3d->config->width)
	{
		cub3d->wall.z_buffer[i] = 0;
		i++;
	}
}

void
	init_screen(t_cub3d *cub3d)
{
	t_screen	screen;

	screen = (t_screen){.mapX = 0, .mapY = 0, .planeX = 0, .planeY = 0,
		.color = 0};
	cub3d->screen = screen;
}
