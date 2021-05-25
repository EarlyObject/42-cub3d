/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 22:09:23 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/25 22:11:50 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

int
	deal_key(int key_code, t_cub3d *cub3d)
{
	if (key_code == KEY_ESC)
	{
		exit(0);
	}
	if (key_code == KEY_W || key_code == KEY_FORWARD)
		cub3d->plr.walkDrcn = +1;
	if (key_code == KEY_S || key_code == KEY_BACKWARD)
		cub3d->plr.walkDrcn = -1;
	if (key_code == KEY_RIGHT)
		cub3d->plr.turnDrcn = +1;
	if (key_code == KEY_LEFT)
		cub3d->plr.turnDrcn = -1;
	if (key_code == KEY_D)
		cub3d->plr.moveSide = +1;
	if (key_code == KEY_A)
		cub3d->plr.moveSide = -1;
	return (0);
}

int
	key_release(int key_code, t_cub3d *cub3d)
{
	if (key_code == KEY_W || key_code == KEY_FORWARD)
		cub3d->plr.walkDrcn = 0;
	if (key_code == KEY_S || key_code == KEY_BACKWARD)
		cub3d->plr.walkDrcn = 0;
	if (key_code == KEY_RIGHT)
		cub3d->plr.turnDrcn = 0;
	if (key_code == KEY_LEFT)
		cub3d->plr.turnDrcn = 0;
	if (key_code == KEY_D)
		cub3d->plr.moveSide = 0;
	if (key_code == KEY_A)
		cub3d->plr.moveSide = 0;
	return (0);
}

int
	close_win(void)
{
	exit(0);
}
