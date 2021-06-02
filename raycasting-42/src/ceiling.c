/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 19:59:20 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/01 19:59:21 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	draw_floor(t_cub3d *cub3d)
{
	for(int y = cub3d->config->height / 2 + 1; y < cub3d->config->height; ++y)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		float rayDirX0 = cub3d->plr.dirX - cub3d->screen.planeX;
		float rayDirY0 = cub3d->plr.dirY - cub3d->screen.planeY;
		float rayDirX1 = cub3d->plr.dirX + cub3d->screen.planeX;
		float rayDirY1 = cub3d->plr.dirY + cub3d->screen.planeY;

		// Current y position compared to the center of the screen (the horizon)
		int p = y - cub3d->config->height / 2;

		// Vertical position of the camera.
		// NOTE: with 0.5, it's exactly in the center between floor and ceiling,
		// matching also how the walls are being raycasted. For different values
		// than 0.5, a separate loop must be done for ceiling and floor since
		// they're no longer symmetrical.
		float posZ = 0.5 * cub3d->config->height;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		// NOTE: this is affine texture mapping, which is not perspective correct
		// except for perfectly horizontal and vertical surfaces like the floor.
		// NOTE: this formula is explained as follows: The camera ray goes through
		// the following two points: the camera itself, which is at a certain
		// height (posZ), and a point in front of the camera (through an imagined
		// vertical plane containing the screen pixels) with horizontal distance
		// 1 from the camera, and vertical position p lower than posZ (posZ - p). When going
		// through that point, the line has vertically traveled by p units and
		// horizontally by 1 unit. To hit the floor, it instead needs to travel by
		// posZ units. It will travel the same ratio horizontally. The ratio was
		// 1 / p for going through the camera plane, so to go posZ times farther
		// to reach the floor, we get that the total horizontal distance is posZ / p.
		float rowDistance = posZ / p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / cub3d->config->width;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / cub3d->config->width;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = cub3d->plr.posX + rowDistance * rayDirX0;
		float floorY = cub3d->plr.posY + rowDistance * rayDirY0;

		if (cub3d->config->wallTexture[TEX_FLOOR] == NULL)
		{
			for(int x = 0; x < cub3d->config->width; ++x)
			{
				drawPixel(cub3d, x, y, cub3d->config->color[TEX_FLOOR]);
			}
		}
		else
		{
			for(int x = 0; x < cub3d->config->width; ++x)
			{
				// the cell coord is simply got from the integer parts of floorX and floorY
				int cellX = (int)(floorX);
				int cellY = (int)(floorY);

				// get the texture coordinate from the fractional part
				int tx = (int)(TEXTURE_WIDTH * (floorX - cellX)) & (TEXTURE_WIDTH - 1);
				int ty = (int)(TEXTURE_HEIGHT * (floorY - cellY)) & (TEXTURE_HEIGHT - 1);

				floorX += floorStepX;
				floorY += floorStepY;

				//int floorTexture = 4;
				Uint32 color;

				// floor
				uint32_t *walTextrBuf;
				walTextrBuf = cub3d->config->wallTexture[TEX_FLOOR]->addr;
				color = walTextrBuf[(TEXTURE_WIDTH * ty + tx)];
				color = (color >> 1) & 8355711; // make a bit darker
				drawPixel(cub3d, x, y, color);
			}
		}


	}
}

void
	draw_ceiling(t_cub3d *cub3d)
{
	for(int y = 0; y < cub3d->config->height / 2 + 1; ++y)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		float rayDirX0 = cub3d->plr.dirX - cub3d->screen.planeX;
		float rayDirY0 = cub3d->plr.dirY - cub3d->screen.planeY;
		float rayDirX1 = cub3d->plr.dirX + cub3d->screen.planeX;
		float rayDirY1 = cub3d->plr.dirY + cub3d->screen.planeY;

		int p = y - cub3d->config->height / 2;

		float posZ = 0.5 * cub3d->config->height;


		float rowDistance = posZ / p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / cub3d->config->width;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / cub3d->config->width;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = cub3d->plr.posX + rowDistance * rayDirX0;
		float floorY = cub3d->plr.posY + rowDistance * rayDirY0;

		if (cub3d->config->wallTexture[TEX_SKY] == NULL)
		{
			for(int x = 0; x < cub3d->config->width; ++x)
			{
				drawPixel(cub3d, x, y, cub3d->config->color[TEX_SKY]);
			}
		}
		else
		{
			for(int x = 0; x < cub3d->config->width; ++x)
			{
				// the cell coord is simply got from the integer parts of floorX and floorY
				int cellX = (int)(floorX);
				int cellY = (int)(floorY);

				// get the texture coordinate from the fractional part
				int tx = (int)(TEXTURE_WIDTH * (floorX - cellX)) & (TEXTURE_WIDTH - 1);
				int ty = (int)(TEXTURE_HEIGHT * (floorY - cellY)) & (TEXTURE_HEIGHT - 1);

				floorX += floorStepX;
				floorY += floorStepY;

				// choose texture and draw the pixel
				int ceilingTexture = 6;
				Uint32 color;

				// floor
				uint32_t *walTextrBuf;
				walTextrBuf = cub3d->config->wallTexture[ceilingTexture]->addr;
				color = walTextrBuf[(TEXTURE_WIDTH * ty + tx)];
				color = (color >> 1) & 8355711; // make a bit darker
				drawPixel(cub3d, x, y, color);
			}
		}
	}
}