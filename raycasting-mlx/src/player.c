/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:00:43 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/14 14:00:47 by asydykna         ###   ########.fr       */
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
	if (!mapHasWallAt(newPlayerX, newPlayerY))
	{
		cub3d->plr.x = newPlayerX;
		cub3d->plr.y = newPlayerY;
	}
}

void
	renderMapPlayer(t_cub3d *cub3d)
{
	drawRect
	(
		cub3d,
		cub3d->plr.x * MINIMAP_SCALE_FACTOR,
		cub3d->plr.y * MINIMAP_SCALE_FACTOR,
		cub3d->plr.width * MINIMAP_SCALE_FACTOR,
		cub3d->plr.height * MINIMAP_SCALE_FACTOR,
		0xFFFFFFFF
	);
	drawLine
	(
			cub3d,
			MINIMAP_SCALE_FACTOR * cub3d->plr.x,
			MINIMAP_SCALE_FACTOR * cub3d->plr.y,
			MINIMAP_SCALE_FACTOR * cub3d->plr.x + cos(cub3d->plr.rotAngle) * 40,
			MINIMAP_SCALE_FACTOR * cub3d->plr.y + sin(cub3d->plr.rotAngle) * 40,
			RED
	);
}
