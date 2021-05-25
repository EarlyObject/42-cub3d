/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:01:35 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/14 18:15:17 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	changeColorIntensity(uint32_t	*color, float factor)
{
	uint32_t	a;
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	a = (*color & 0xFF000000);
	r = (*color & 0x00FF0000) * factor;
	g = (*color & 0x0000FF00) * factor;
	b = (*color & 0x000000FF) * factor;
	*color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
}

void
	draw_wall(t_cub3d *cub3d, int x)
{
	int			texNum;
	int			y;
	int			distanceFromTop;
	uint32_t	*walTextrBuf;
	uint32_t	texelColor;

	if (cub3d->rays[x].wasHitVertical)
	{
		cub3d->wall.textureOffsetX = (int) cub3d->rays[x].wallHitY % TILE_SIZE;
		texNum = cub3d->rays[x].texture + 2;
		if (cub3d->rays[x].rayAngle > PI /2 && cub3d->rays[x].rayAngle < (PI + PI /2))
			texNum = cub3d->rays[x].texture + 1;
	}
	else
	{
		cub3d->wall.textureOffsetX = (int) cub3d->rays[x].wallHitX % TILE_SIZE;
		if (cub3d->rays[x].rayAngle   < PI )
			texNum = cub3d->rays[x].texture;
		else if (cub3d->rays[x].rayAngle   > PI)
			texNum = cub3d->rays[x].texture - 1;
	}
	y = cub3d->wall.wallTopY - 1;
	while (y++ < cub3d->wall.wallBottomY)
	{
		distanceFromTop = (y + (cub3d->wall.wallHeight / 2)
						   - (cub3d->config->height / 2));
		cub3d->wall.textureOffsetY = distanceFromTop
									 * (float)(TEXTURE_HEIGHT / cub3d->wall.wallHeight);
		if (cub3d->wall.textureOffsetY > 63)
			cub3d->wall.textureOffsetY = 63;
		/*if (cub3d->wall.textureOffsetX > 63)
			cub3d->wall.textureOffsetX = 63;*/
		if(cub3d->config->wallTexture[texNum])
		{
			/*if (texNum < 0)
				texNum = 0;*/
			//printf("texnum = %d, textureOffsetX = %d, textureOffsetY = %d\n", texNum, cub3d->wall.textureOffsetX, cub3d->wall.textureOffsetY);
			walTextrBuf = (uint32_t *) cub3d->config->wallTexture[texNum]->addr;
			texelColor = walTextrBuf[(TEXTURE_WIDTH * cub3d->wall.textureOffsetY + cub3d->wall.textureOffsetX)];
		}
		else
			texelColor = cub3d->config->color[cub3d->rays[x].texture];
		if (cub3d->rays[x].wasHitVertical)
			changeColorIntensity(&texelColor, 0.7);
		drawPixel(cub3d, x, y, texelColor);
	}
}

void
	calc_wall(t_cub3d *cub3d, int x)
{
	float	perpDistance;

	perpDistance = cub3d->rays[x].distance
				   * cos(cub3d->rays[x].rayAngle - cub3d->plr.rotAngle);
	cub3d->wall.wallHeight = (TILE_SIZE / perpDistance) * cub3d->config->dist_proj_plane;
	cub3d->wall.wallTopY = (cub3d->config->height / 2) - (cub3d->wall.wallHeight / 2);
	if (cub3d->wall.wallTopY < 0)
		cub3d->wall.wallTopY = 0;
	cub3d->wall.wallBottomY = (cub3d->config->height / 2)
							  + (cub3d->wall.wallHeight / 2);
	if (cub3d->wall.wallBottomY > cub3d->config->height)
		cub3d->wall.wallBottomY = cub3d->config->height;
	if (cub3d->wall.wallBottomY < 0)
		cub3d->wall.wallBottomY = 0;
}

void
	renderWallProjection(t_cub3d *cub3d)
{
	int		x;
	int		y;
	int num_rays;

	num_rays = cub3d->config->width;
	x = 0;
	while (x < num_rays)
	{
		calc_wall(cub3d, x);
		y = 0;
		while (y < cub3d->wall.wallTopY)
		{
			drawPixel(cub3d, x, y, cub3d->config->color[TEX_SKY]);
			y++;
		}
		draw_wall(cub3d, x);
		y = cub3d->wall.wallBottomY;
		while (y < cub3d->config->height)
		{
			drawPixel(cub3d, x, y, cub3d->config->color[TEX_FLOOR]);
				y++;
		}
		x++;
	}
}
