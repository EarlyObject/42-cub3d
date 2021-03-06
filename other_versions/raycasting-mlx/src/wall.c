/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:01:35 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/28 09:29:31 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

uint32_t
	get_texel_color(t_cub3d *cub3d, int x, int texNum, int y)
{
uint32_t	texelColor;
uint32_t	*walTextrBuf;
int			distanceFromTop;

distanceFromTop = (y + (cub3d->wall.wallHeight / 2)
				   - (cub3d->config->height / 2));
cub3d->wall.textureOffsetY = distanceFromTop
							 * (float)(TEXTURE_HEIGHT / cub3d->wall.wallHeight);
if (cub3d->wall.textureOffsetY > 63)
cub3d->wall.textureOffsetY = 63;
/*if (cub3d->wall.textureOffsetX > 63)
cub3d->wall.textureOffsetX = 63;*/
if (cub3d->config->wallTexture[texNum])
{
if (texNum < 0)
texNum = 0;
/*printf("texNum = %d, textureOffsetX = %d, textureOffsetY = %d\n", texNum, cub3d->wall.textureOffsetX, cub3d->wall.textureOffsetY);*/
walTextrBuf = (uint32_t *) cub3d->config->wallTexture[texNum]->addr;
if (walTextrBuf == NULL)
printf("walTextrBuf = NULL");
texelColor = walTextrBuf[(TEXTURE_WIDTH * cub3d->wall.textureOffsetY)
						 + cub3d->wall.textureOffsetX];
//texelColor = GREEN;
}
else
texelColor = cub3d->config->color[cub3d->rays[x].texture];
return (texelColor);
}

void
	draw_wall(t_cub3d *cub3d, int x)
{
	int			texNum;
	int			y;
	uint32_t	texelColor;

	if (cub3d->rays[x].wasHitVertical)
	{
		cub3d->wall.textureOffsetX = (int) cub3d->rays[x].wallHitY % TILE_SIZE;
		texNum = cub3d->rays[x].texture + 2;
		if (cub3d->rays[x].rayAngle >= PI / 2
			&& cub3d->rays[x].rayAngle <= (PI + PI / 2))
			texNum = cub3d->rays[x].texture + 1;
	}
	else
	{
		cub3d->wall.textureOffsetX = (int) cub3d->rays[x].wallHitX % TILE_SIZE;
		if (cub3d->rays[x].rayAngle <= PI)
			texNum = cub3d->rays[x].texture;
		else if (cub3d->rays[x].rayAngle >= PI)
			texNum = cub3d->rays[x].texture - 1;
	}
	y = cub3d->wall.wallTopY;
	while (y < cub3d->wall.wallBottomY)
	{
		texelColor = get_texel_color(cub3d, x, texNum, y);
		if (cub3d->rays[x].wasHitVertical)
			changeColorIntensity(&texelColor, 0.7);
		drawPixel(cub3d, x, y, texelColor);
		y++;
	}
}

void
	calc_wall(t_cub3d *cub3d, int x)
{
	float	perp_distance;

	perp_distance = cub3d->rays[x].distance
					* cos(cub3d->rays[x].rayAngle - cub3d->plr.rotAngle);
	cub3d->wall.wallHeight = (TILE_SIZE / perp_distance)
							 * cub3d->config->dist_proj_plane;
	cub3d->wall.wallTopY = (cub3d->config->height / 2)
						   - (cub3d->wall.wallHeight / 2);
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
	int		num_rays;

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
