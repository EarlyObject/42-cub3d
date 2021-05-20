/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:00:43 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/16 17:37:15 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	movePlayer(t_cub3d *cub3d, float dTime)
{
	float	moveStep;
	float	newPlayerX;
	float	newPlayerY;

	cub3d->plr.rotAngle += cub3d->plr.turnDrcn * cub3d->plr.turnSpeed * dTime;
	normalizeAngle(&cub3d->plr.rotAngle);
	moveStep = cub3d->plr.walkDrcn * cub3d->plr.walkSpeed * dTime;
	newPlayerX = cub3d->plr.x + cos(cub3d->plr.rotAngle) * moveStep;
	newPlayerY = cub3d->plr.y + sin(cub3d->plr.rotAngle) * moveStep;

	if (!mapHasWallAt(cub3d->config, newPlayerX, newPlayerY))
	{
		cub3d->plr.x = newPlayerX;
		cub3d->plr.y = newPlayerY;
	}
	if(cub3d->plr.rotAngle >0 && cub3d->plr.rotAngle < PI /2)
	{
		printf("> 0 && < PI\n");
	}
	if(cub3d->plr.rotAngle > (PI / 2) && cub3d->plr.rotAngle < PI)
	{
		printf("> PI/2 && < PI\n");
	}
	if(cub3d->plr.rotAngle > PI && cub3d->plr.rotAngle < (PI + PI /2))
	{
		printf("> PI && < PI +  PI/2\n");
	}
	else
	{
		printf("> PI + PI/2 && < 2PI\n");
	}
}

void
	renderMapPlayer(t_cub3d *cub3d)
{
	t_rectangle	rectangle;
	t_line		line;

	rectangle = (t_rectangle){.x = cub3d->plr.x * MINIMAP_SCALE_FACTOR,
		.y = cub3d->plr.y * MINIMAP_SCALE_FACTOR,
		.width = cub3d->plr.width * MINIMAP_SCALE_FACTOR,
		.height = cub3d->plr.height * MINIMAP_SCALE_FACTOR};
	drawRect(cub3d, rectangle, 0xFFFFFFFF);
	line = (t_line){.x0 = MINIMAP_SCALE_FACTOR * cub3d->plr.x,
		.y0 = MINIMAP_SCALE_FACTOR * cub3d->plr.y,
		.x1 = MINIMAP_SCALE_FACTOR * cub3d->plr.x
		+ cos(cub3d->plr.rotAngle) * 30,
		.y1 = MINIMAP_SCALE_FACTOR * cub3d->plr.y
		+ sin(cub3d->plr.rotAngle) * 30};
	drawLine(cub3d, line, RED);
}
