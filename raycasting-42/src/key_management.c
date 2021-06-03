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

int
	deal_key(int key_code, t_cub3d *cub3d)
{
	double	oldDirX;
	double	oldPlaneX;

	if (key_code == KEY_ESC)
		exit(0);
	if (key_code == KEY_W || key_code == KEY_FORWARD)
		move_forward(cub3d);
	if (key_code == KEY_S || key_code == KEY_BACKWARD)
		move_backward(cub3d);
	if (key_code == KEY_RIGHT || key_code == KEY_LEFT)
	{
		oldDirX = cub3d->plr.dirX;
		oldPlaneX = cub3d->screen.planeX;
		if (key_code == KEY_RIGHT)
			look_right(cub3d, oldDirX, oldPlaneX);
		if (key_code == KEY_LEFT)
			look_left(cub3d, oldDirX, oldPlaneX);
	}
	if (key_code == KEY_D || key_code == KEY_A)
		move_aside(key_code, cub3d);
	return (0);
}

/*int
	key_release(int key_code, t_cub3d *cub3d)
{
	if (key_code == KEY_W || key_code == KEY_FORWARD)
		//cub3d->plr.walkDrcn = 0;
	if (key_code == KEY_S || key_code == KEY_BACKWARD)
		//cub3d->plr.walkDrcn = 0;
	if (key_code == KEY_RIGHT)
		//cub3d->plr.turnDrcn = 0;
	if (key_code == KEY_LEFT)
		//cub3d->plr.turnDrcn = 0;
	if (key_code == KEY_D)
		//cub3d->plr.moveSide = 0;
	if (key_code == KEY_A)
		//cub3d->plr.moveSide = 0;
	return (0);
}*/

int
	close_win(void)
{
	exit(0);
}
