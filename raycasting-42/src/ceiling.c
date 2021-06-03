/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 19:59:20 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/04 14:51:29 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

uint32_t
	get_texture_color(t_cub3d *cub3d)
{
	int			cellX;
	int			cellY;
	int			tx;
	int			ty;

	cellX = (int)(cub3d->screen.floorX);
	cellY = (int)(cub3d->screen.floorY);
	tx = (int)(TEXTURE_WIDTH
			   * (cub3d->screen.floorX - cellX)) & (TEXTURE_WIDTH - 1);
	ty = (int)(TEXTURE_HEIGHT
			   * (cub3d->screen.floorY - cellY)) & (TEXTURE_HEIGHT - 1);
	cub3d->screen.floorX += cub3d->screen.floorStepX;
	cub3d->screen.floorY += cub3d->screen.floorStepY;
	cub3d->screen.walTextrBuf = cub3d->config->wallTexture[TEX_FLOOR]->addr;
	cub3d->screen.color = cub3d->screen.walTextrBuf[(TEXTURE_WIDTH * ty + tx)];
	cub3d->screen.color = (cub3d->screen.color >> 1) & 8355711;
	return (cub3d->screen.color);
}

void
	calc_floor_ceiling_params(t_cub3d *cub3d, int start)
{
	int		p;
	float	posZ;
	float	rowDistance;

	cub3d->screen.rayDirX0 = cub3d->plr.dirX - cub3d->screen.planeX;
	cub3d->screen.rayDirY0 = cub3d->plr.dirY - cub3d->screen.planeY;
	cub3d->screen.rayDirX1 = cub3d->plr.dirX + cub3d->screen.planeX;
	cub3d->screen.rayDirY1 = cub3d->plr.dirY + cub3d->screen.planeY;
	p = start - cub3d->config->height / 2;
	posZ = 0.5 * cub3d->config->height;
	rowDistance = posZ / p;
	cub3d->screen.floorStepX = rowDistance * (cub3d->screen.rayDirX1
			- cub3d->screen.rayDirX0) / cub3d->config->width;
	cub3d->screen.floorStepY = rowDistance * (cub3d->screen.rayDirY1
			- cub3d->screen.rayDirY0) / cub3d->config->width;
	cub3d->screen.floorX = cub3d->plr.posX + rowDistance
		* cub3d->screen.rayDirX0;
	cub3d->screen.floorY = cub3d->plr.posY + rowDistance
		* cub3d->screen.rayDirY0;
}

void
	draw_floor_ceiling(t_cub3d *cub3d, int start, int end, int texnum)
{
	int			x;
	uint32_t	color;

	while (start < end)
	{
		calc_floor_ceiling_params(cub3d, start);
		if (cub3d->config->wallTexture[texnum] == NULL)
		{
			x = -1;
			while (x++ < cub3d->config->width)
				drawPixel(cub3d, x, start, cub3d->config->color[texnum]);
		}
		else
		{
			x = 0;
			while (x < cub3d->config->width)
			{
				color = get_texture_color(cub3d);
				drawPixel(cub3d, x, start, color);
				x++;
			}
		}
		start++;
	}
}
