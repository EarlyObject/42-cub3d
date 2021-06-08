/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:00:43 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/13 19:10:56 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	look_left(t_cub3d *cub3d, double oldDirX, double oldPlaneX)
{
	cub3d->plr.dirX = cub3d->plr.dirX * cos(-ROT)
		- cub3d->plr.dirY * sin(-ROT);
	cub3d->plr.dirY = oldDirX * sin(-ROT)
		 + cub3d->plr.dirY * cos(-ROT);
	cub3d->screen.planeX = cub3d->screen.planeX * cos(-ROT)
		- cub3d->screen.planeY * sin(-ROT);
	cub3d->screen.planeY = oldPlaneX * sin(-ROT)
		+ cub3d->screen.planeY * cos(-ROT);
}

void
	look_right(t_cub3d *cub3d, double oldDirX, double oldPlaneX)
{
	cub3d->plr.dirX = cub3d->plr.dirX * cos(ROT)
		- cub3d->plr.dirY * sin(ROT);
	cub3d->plr.dirY = oldDirX * sin(ROT)
		+ cub3d->plr.dirY * cos(ROT);
	cub3d->screen.planeX = cub3d->screen.planeX * cos(ROT)
		- cub3d->screen.planeY * sin(ROT);
	cub3d->screen.planeY = oldPlaneX * sin(ROT)
		+ cub3d->screen.planeY * cos(ROT);
}

void
	move_left(t_cub3d *cub3d)
{
	int	mx_x;
	int	mx_y;
	int	my_x;
	int	my_y;

	mx_x = (int)(cub3d->plr.posX - cub3d->screen.planeX * MOVE_SPEED);
	mx_y = (int)(cub3d->plr.posY);
	my_x = (int)(cub3d->plr.posX);
	my_y = (int)(cub3d->plr.posY - cub3d->screen.planeY * MOVE_SPEED);
	if (cub3d->config->map[mx_x + mx_y * cub3d->config->max_len] != '1')
		cub3d->plr.posX -= cub3d->screen.planeX * MOVE_SPEED;
	if (cub3d->config->map[my_x + my_y * cub3d->config->max_len] != '1')
		cub3d->plr.posY -= cub3d->screen.planeY * MOVE_SPEED;
}

void
	move_right(t_cub3d *cub3d)
{
	int	mx_x;
	int	mx_y;
	int	my_x;
	int	my_y;

	mx_x = (int)(cub3d->plr.posX + cub3d->screen.planeX * MOVE_SPEED);
	mx_y = (int)(cub3d->plr.posY);
	my_x = (int)(cub3d->plr.posX);
	my_y = (int)(cub3d->plr.posY + cub3d->screen.planeY * MOVE_SPEED);
	if (cub3d->config->map[mx_x + mx_y * cub3d->config->max_len] != '1')
		cub3d->plr.posX += cub3d->screen.planeX * MOVE_SPEED;
	if (cub3d->config->map[my_x + my_y * cub3d->config->max_len] != '1')
		cub3d->plr.posY += cub3d->screen.planeY * MOVE_SPEED;
}

void
	move_forward(t_cub3d *cub3d)
{
	int	mx_x;
	int	mx_y;
	int	my_x;
	int	my_y;

	mx_x = (int)(cub3d->plr.posX + cub3d->plr.dirX * MOVE_SPEED);
	mx_y = (int)(cub3d->plr.posY);
	my_x = (int)(cub3d->plr.posX);
	my_y = (int)(cub3d->plr.posY + cub3d->plr.dirY * MOVE_SPEED);
	if (cub3d->config->map[mx_x + mx_y * cub3d->config->max_len] != '1')
		cub3d->plr.posX += cub3d->plr.dirX * MOVE_SPEED;
	if (cub3d->config->map[my_x + my_y * cub3d->config->max_len] != '1')
		cub3d->plr.posY += cub3d->plr.dirY * MOVE_SPEED;
}
