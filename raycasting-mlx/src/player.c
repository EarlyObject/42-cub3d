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
	float	stepY;
	float	stepX;

	cub3d->plr.rotAngle += cub3d->plr.turnDrcn * cub3d->plr.turnSpeed * dTime;
	moveStep = cub3d->plr.walkDrcn * cub3d->plr.walkSpeed * dTime;
	if (cub3d->plr.moveSide)
	{
		float ang;
		if (cub3d->plr.rotAngle >= 0 && cub3d->plr.rotAngle <= PI / 2)
			ang = TWO_PI - cub3d->plr.rotAngle;
		else if (cub3d->plr.rotAngle > PI / 2 && cub3d->plr.rotAngle < PI)
			ang = cub3d->plr.rotAngle;
		else if (cub3d->plr.rotAngle >= PI && cub3d->plr.rotAngle < (PI + PI /2))
			ang = cub3d->plr.rotAngle;
		else
			ang = TWO_PI-cub3d->plr.rotAngle;
		stepY = cos(ang) * 2;
		stepX = sin(ang) * stepY;
		if (cub3d->plr.moveSide > 0)
		{
			newPlayerX = cub3d->plr.x + stepX;
			newPlayerY = cub3d->plr.y + stepY;
		}
		else
		{
			newPlayerX = cub3d->plr.x - stepX;
			newPlayerY = cub3d->plr.y - stepY;
		}
	}
	else
	{
		normalizeAngle(&cub3d->plr.rotAngle);
		newPlayerX = cub3d->plr.x + cos(cub3d->plr.rotAngle) * moveStep;
		newPlayerY = cub3d->plr.y + sin(cub3d->plr.rotAngle) * moveStep;
	}
	if (!mapHasWallAt(cub3d->config, newPlayerX, newPlayerY))
	{
		cub3d->plr.x = newPlayerX;
		cub3d->plr.y = newPlayerY;
	}
}

void
	renderMapPlayer(t_cub3d *cub3d)
{
	t_rectangle	rectangle;

	rectangle = (t_rectangle){.x = cub3d->plr.x * MINIMAP_SCALE_FACTOR,
		.y = cub3d->plr.y * MINIMAP_SCALE_FACTOR,
		.width = cub3d->plr.width * MINIMAP_SCALE_FACTOR,
		.height = cub3d->plr.height * MINIMAP_SCALE_FACTOR};
	drawRect(cub3d, rectangle, 0xFFFFFFFF);
}
