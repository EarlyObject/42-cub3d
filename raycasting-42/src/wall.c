/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:01:35 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/06 19:57:14 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	perform_dda(t_cub3d *cub3d)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (cub3d->wall.sideDistX < cub3d->wall.sideDistY)
		{
			cub3d->wall.sideDistX += cub3d->wall.deltaDistX;
			(cub3d->screen.mapX) += cub3d->wall.stepX;
			(cub3d->wall.side) = 0;
		}
		else
		{
			cub3d->wall.sideDistY += cub3d->wall.deltaDistY;
			(cub3d->screen.mapY) += cub3d->wall.stepY;
			(cub3d->wall.side) = 1;
		}
		if (cub3d->config->map[(cub3d->screen.mapX)
				+ (cub3d->config->columns * (cub3d->screen.mapY))] == '1')
			hit = 1;
	}
}

void
	calc_step_and_side_dist(t_cub3d *cub3d)
{
	if (cub3d->wall.rayDirX < 0)
	{
		cub3d->wall.stepX = -1;
		cub3d->wall.sideDistX = (cub3d->plr.posX - cub3d->screen.mapX)
			* cub3d->wall.deltaDistX;
	}
	else
	{
		cub3d->wall.stepX = 1;
		cub3d->wall.sideDistX = (cub3d->screen.mapX + 1.0 - cub3d->plr.posX)
			* cub3d->wall.deltaDistX;
	}
	if (cub3d->wall.rayDirY < 0)
	{
		cub3d->wall.stepY = -1;
		cub3d->wall.sideDistY = (cub3d->plr.posY - cub3d->screen.mapY)
			* cub3d->wall.deltaDistY;
	}
	else
	{
		cub3d->wall.stepY = 1;
		cub3d->wall.sideDistY = (cub3d->screen.mapY + 1.0 - cub3d->plr.posY)
			* cub3d->wall.deltaDistY;
	}
}

void
	draw_walls(t_cub3d *cub3d, int x, int start, int end)
{
	int	texY;

	while (start < end)
	{
		if (!cub3d->config->wallTexture[cub3d->wall.texNum])
			draw_pixel(cub3d, x, start, cub3d->config
				->color[cub3d->wall.texNum]);
		else
		{
			texY = (int) cub3d->wall.texPos & (TEXTURE_HEIGHT - 1);
			cub3d->wall.texPos += cub3d->wall.step;
			cub3d->wall.walTextrBuf
				= cub3d->config->wallTexture[cub3d->wall.texNum]->addr;
			cub3d->screen.color = cub3d->wall.walTextrBuf[(TEXTURE_HEIGHT
					* texY + cub3d->wall.texX)];
			if (cub3d->wall.side == 1)
				cub3d->screen.color = (cub3d->screen.color >> 1) & 8355711;
			draw_pixel(cub3d, x, start, cub3d->screen.color);
		}
		start++;
	}
}

void
	calc_ray(t_cub3d *cub3d, int x)
{
	double	cameraX;

	cameraX = 2 * x / (double)(cub3d->config->width) - 1;
	cub3d->wall.rayDirX = cub3d->plr.dirX + cub3d->screen.planeX * cameraX;
	cub3d->wall.rayDirY = cub3d->plr.dirY + cub3d->screen.planeY * cameraX;
	cub3d->screen.mapX = (int)cub3d->plr.posX;
	cub3d->screen.mapY = (int)cub3d->plr.posY;
	cub3d->wall.deltaDistX = fabs(1 / cub3d->wall.rayDirX);
	cub3d->wall.deltaDistY = fabs(1 / cub3d->wall.rayDirY);
}

void
	calc_wall_x(t_cub3d *cub3d)
{
	if (cub3d->wall.side == 0)
	{
		cub3d->wall.wallX = cub3d->plr.posY + cub3d->wall.perpWallDist
			* cub3d->wall.rayDirY;
		if (cub3d->wall.rayDirX > 0)
			cub3d->wall.texNum += 3;
		else
			cub3d->wall.texNum += 2;
	}
	else
	{
		cub3d->wall.wallX = cub3d->plr.posX + cub3d->wall.perpWallDist
			* cub3d->wall.rayDirX;
		if (cub3d->wall.rayDirY < 0)
			cub3d->wall.texNum += 0;
		else
			cub3d->wall.texNum += 1;
	}
	cub3d->wall.wallX -= floor((cub3d->wall.wallX));
}
