/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 18:34:41 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/03 18:35:21 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	move_player(t_cub3d *cub3d)
{
	double	oldDirX;
	double	oldPlaneX;

	if (cub3d->keys.left)
	{
		oldDirX = cub3d->plr.dirX;
		oldPlaneX = cub3d->screen.planeX;
		look_left(cub3d, oldDirX, oldPlaneX);
	}
	if (cub3d->keys.right)
	{
		oldDirX = cub3d->plr.dirX;
		oldPlaneX = cub3d->screen.planeX;
		look_right(cub3d, oldDirX, oldPlaneX);
	}
	if (cub3d->keys.w)
		move_forward(cub3d);
	if (cub3d->keys.s)
		move_backward(cub3d);
	if (cub3d->keys.a)
		move_left(cub3d);
	if (cub3d->keys.d)
		move_right(cub3d);
}

int
	deal_key(int key_code, t_cub3d *cub3d)
{
	if (key_code == KEY_ESC)
		exit(0);
	if (key_code == KEY_W)
		cub3d->keys.w = true;
	if (key_code == KEY_S)
		cub3d->keys.s = true;
	if (key_code == KEY_D)
		cub3d->keys.d = true;
	if (key_code == KEY_A)
		cub3d->keys.a = true;
	if (key_code == KEY_RIGHT)
		cub3d->keys.right = true;
	if (key_code == KEY_LEFT)
		cub3d->keys.left = true;
	return (0);
}

int
	release_key(int key_code, t_cub3d *cub3d)
{
	if (key_code == KEY_W)
		cub3d->keys.w = false;
	if (key_code == KEY_S)
		cub3d->keys.s = false;
	if (key_code == KEY_D)
		cub3d->keys.d = false;
	if (key_code == KEY_A)
		cub3d->keys.a = false;
	if (key_code == KEY_RIGHT)
		cub3d->keys.right = false;
	if (key_code == KEY_LEFT)
		cub3d->keys.left = false;
	return (0);
}

int
	close_win(void)
{
	exit(0);
}

void
	move_backward(t_cub3d *cub3d)
{
	int	mx_x;
	int	mx_y;
	int	my_x;
	int	my_y;

	mx_x = (int)(cub3d->plr.posX - cub3d->plr.dirX * MOVE_SPEED);
	mx_y = (int)(cub3d->plr.posY);
	my_x = (int)(cub3d->plr.posX);
	my_y = (int)(cub3d->plr.posY - cub3d->plr.dirY * MOVE_SPEED);
	if (cub3d->config->map[mx_x + mx_y * cub3d->config->max_len] != '1')
		cub3d->plr.posX -= cub3d->plr.dirX * MOVE_SPEED;
	if (cub3d->config->map[my_x + my_y * cub3d->config->max_len] != '1')
		cub3d->plr.posY -= cub3d->plr.dirY * MOVE_SPEED;
}
