/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:00:43 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/03 18:35:10 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	look_left(t_cub3d *cub3d, double oldDirX, double oldPlaneX)
{
	cub3d->plr.dirX = cub3d->plr.dirX * cos(cub3d->plr.rotSpeed)
		- cub3d->plr.dirY * sin(cub3d->plr.rotSpeed);
	cub3d->plr.dirY = oldDirX * sin(cub3d->plr.rotSpeed)
		+ cub3d->plr.dirY * cos(cub3d->plr.rotSpeed);
	cub3d->screen.planeX = cub3d->screen.planeX * cos(cub3d->plr.rotSpeed)
		- cub3d->screen.planeY * sin(cub3d->plr.rotSpeed);
	cub3d->screen.planeY = oldPlaneX * sin(cub3d->plr.rotSpeed)
		+ cub3d->screen.planeY * cos(cub3d->plr.rotSpeed);
}

void
	look_right(t_cub3d *cub3d, double oldDirX, double oldPlaneX)
{
	cub3d->plr.dirX = cub3d->plr.dirX * cos(-cub3d->plr.rotSpeed)
		- cub3d->plr.dirY * sin(-cub3d->plr.rotSpeed);
	cub3d->plr.dirY = oldDirX * sin(-cub3d->plr.rotSpeed)
		+ cub3d->plr.dirY * cos(-cub3d->plr.rotSpeed);
	cub3d->screen.planeX = cub3d->screen.planeX * cos(-cub3d->plr.rotSpeed)
		- cub3d->screen.planeY * sin(-cub3d->plr.rotSpeed);
	cub3d->screen.planeY = oldPlaneX * sin(-cub3d->plr.rotSpeed)
		+ cub3d->screen.planeY * cos(-cub3d->plr.rotSpeed);
}

void
	move_aside(int key_code, t_cub3d *cub3d)
{
	if (key_code == KEY_D)
	{
		if (cub3d->config->map[(int)((cub3d->plr.posX + cub3d->screen.planeX
					* cub3d->plr.moveSpeed) + (cub3d->config->columns
					* (int)cub3d->plr.posY))] == '0')
			cub3d->plr.posX += cub3d->screen.planeX * cub3d->plr.moveSpeed;
		if (cub3d->config->map[(int)((cub3d->plr.posX) + (cub3d->config->columns
					* (int)(cub3d->plr.posY + cub3d->screen.planeY
					* cub3d->plr.moveSpeed)))] == '0')
			cub3d->plr.posY += cub3d->screen.planeY * cub3d->plr.moveSpeed;
	}
	if (key_code == KEY_A)
	{
		if (cub3d->config->map[(int)(cub3d->plr.posX - cub3d->screen.planeX
				* cub3d->plr.moveSpeed) + (cub3d->config->columns
				* (int)cub3d->plr.posY)] == '0')
			cub3d->plr.posX -= cub3d->screen.planeX * cub3d->plr.moveSpeed;
		if (cub3d->config->map[(int)(cub3d->plr.posX) + (cub3d->config->columns
				* (int)(cub3d->plr.posY - cub3d->screen.planeY
				* cub3d->plr.moveSpeed))] == '0')
			cub3d->plr.posY -= cub3d->screen.planeY * cub3d->plr.moveSpeed;
	}
}

void
	move_forward(t_cub3d *cub3d)
{
	if (cub3d->config->map[(int)(cub3d->plr.posX + cub3d->plr.dirX
			* cub3d->plr.moveSpeed) + (cub3d->config->columns
			* (int)(cub3d->plr.posY))] - 48 == false)
		cub3d->plr.posX += cub3d->plr.dirX * cub3d->plr.moveSpeed;
	if (cub3d->config->map[(int)(cub3d->plr.posX) + (cub3d->config->columns
			* (int)(cub3d->plr.posY + cub3d->plr.dirY
			* cub3d->plr.moveSpeed))] - 48 == false)
		cub3d->plr.posY += cub3d->plr.dirY * cub3d->plr.moveSpeed;
}

void
	move_backward(t_cub3d *cub3d)
{
	if (cub3d->config->map[(int)(cub3d->plr.posX - cub3d->plr.dirX
			* cub3d->plr.moveSpeed) + (cub3d->config->columns
			* (int)(cub3d->plr.posY))] - 48 == false)
		cub3d->plr.posX -= cub3d->plr.dirX * cub3d->plr.moveSpeed;
	if (cub3d->config->map[(int)(cub3d->plr.posX) + (cub3d->config->columns
			* (int)(cub3d->plr.posY - cub3d->plr.dirY
			* cub3d->plr.moveSpeed))] - 48 == false)
		cub3d->plr.posY -= cub3d->plr.dirY * cub3d->plr.moveSpeed;
}
