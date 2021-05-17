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

	/*if (rays[x].wasHitVertical)
		cub3d->wall.textureOffsetX = (int) rays[x].wallHitY % TILE_SIZE;
	else
		cub3d->wall.textureOffsetX = (int) rays[x].wallHitX % TILE_SIZE;
	texNum = rays[x].texture - 1;*/
	if (cub3d->rays[x].wasHitVertical)
		cub3d->wall.textureOffsetX = (int) cub3d->rays[x].wallHitY % TILE_SIZE;
	else
		cub3d->wall.textureOffsetX = (int) cub3d->rays[x].wallHitX % TILE_SIZE;
	texNum = cub3d->rays[x].texture - 1;
	y = cub3d->wall.wallTopY - 1;
	while (y++ < cub3d->wall.wallBottomY)
	{
		//distanceFromTop = (y + (cub3d->wall.wallHeight / 2)
		//		- (WINDOW_HEIGHT / 2));
		distanceFromTop = (y + (cub3d->wall.wallHeight / 2)
						   - (cub3d->config->requested_height / 2));
		cub3d->wall.textureOffsetY = distanceFromTop
			* ((float) TEXTURE_HEIGHT / cub3d->wall.wallHeight);
		walTextrBuf = (uint32_t *) cub3d->wallTexture[texNum]->addr;
		texelColor = walTextrBuf[(TEXTURE_WIDTH * cub3d->wall.textureOffsetY)
			+ cub3d->wall.textureOffsetX];
		//if (rays[x].wasHitVertical)
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
	cub3d->wall.wallTopY = (cub3d->config->requested_height / 2) - (cub3d->wall.wallHeight / 2);
	if (cub3d->wall.wallTopY < 0)
		cub3d->wall.wallTopY = 0;
	cub3d->wall.wallBottomY = (cub3d->config->requested_height / 2)
							  + (cub3d->wall.wallHeight / 2);
	if (cub3d->wall.wallBottomY > cub3d->config->requested_height)
		cub3d->wall.wallBottomY = cub3d->config->requested_height;
	if (cub3d->wall.wallBottomY < 0)
		cub3d->wall.wallBottomY = 0;
}

void
	renderWallProjection(t_cub3d *cub3d)
{
	int		x;
	int		y;
	int num_rays;

	num_rays = cub3d->config->requested_width;
	x = 0;
	while (x < num_rays)
	{
		calc_wall(cub3d, x);
		y = 0;
		while (y < cub3d->wall.wallTopY)
		{
			drawPixel(cub3d, x, y, 0x444444);
			y++;
		}
		draw_wall(cub3d, x);
		y = cub3d->wall.wallBottomY;
		//while (y < WINDOW_HEIGHT)
		while (y < cub3d->config->requested_height)

			{
			drawPixel(cub3d, x, y, 0x777777);
			y++;
		}
		x++;
	}
}
