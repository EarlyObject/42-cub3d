/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:00:43 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/25 22:21:49 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	calc_side_movement(const t_cub3d *cub3d, float *new_pl_x, float *new_pl_y)
{
	float	stepX;
	float	stepY;
	float	ang;

	if (cub3d->plr.rotAngle >= 0 && cub3d->plr.rotAngle <= PI / 2)
		ang = TWO_PI - cub3d->plr.rotAngle;
	else if (cub3d->plr.rotAngle > PI / 2 && cub3d->plr.rotAngle < PI)
		ang = cub3d->plr.rotAngle;
	else if (cub3d->plr.rotAngle >= PI && cub3d->plr.rotAngle < (PI + PI / 2))
		ang = cub3d->plr.rotAngle;
	else
		ang = TWO_PI - cub3d->plr.rotAngle;
	stepY = cos(ang) * 3;
	stepX = sin(ang) * stepY * 3;
	if (cub3d->plr.moveSide > 0)
	{
		(*new_pl_x) = cub3d->plr.x + stepX;
		(*new_pl_y) = cub3d->plr.y + stepY;
	}
	else
	{
		(*new_pl_x) = cub3d->plr.x - stepX;
		(*new_pl_y) = cub3d->plr.y - stepY;
	}
}

void
	movePlayer(t_cub3d *cub3d, float dTime)
{
	float	moveStep;
	float	newPlayerX;
	float	newPlayerY;

	cub3d->plr.rotAngle += cub3d->plr.turnDrcn * cub3d->plr.turnSpeed * dTime;
	moveStep = cub3d->plr.walkDrcn * cub3d->plr.walkSpeed * dTime;
	if (cub3d->plr.moveSide)
	{
		calc_side_movement(cub3d, &newPlayerX, &newPlayerY);
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
