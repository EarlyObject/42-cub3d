/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:00:52 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/16 17:38:02 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

t_ray rays[NUM_RAYS];

bool
	isRayFacingDown(float angle)
{
	return (angle > 0 && angle < PI);
}

bool
	isRayFacingUp(float angle)
{
	return (!isRayFacingDown(angle));
}

bool
	isRayFacingRight(float angle)
{
	return (angle < 0.5 * PI || angle > 1.5 * PI);
}

bool
	isRayFacingLeft(float angle)
{
	return (!isRayFacingRight(angle));
}

void
	castRay(t_cub3d *cub3d, float rayAngle, int stripId)
{
	normalizeAngle(&rayAngle);
	
	float xintercept, yintercept;
	float xstep, ystep;

	/////////////////////////////////////////
	//HORIZONTAL RAY-GRID INTERSECTION CODE
	/////////////////////////////////////////
	bool foundHorzWallHit = false;
	float horzWallHitX = 0;
	float horzWallHitY = 0;
	int horzWallTexture = 0;

	//Find the y-coordinate of the closest horizontal grid intersection
	yintercept = floor(cub3d->plr.y / TILE_SIZE) * TILE_SIZE;
	yintercept += isRayFacingDown(rayAngle) ? TILE_SIZE : 0;

	//Find the x-coordinate of the closest horizontal grid intersection
	xintercept = cub3d->plr.x + (yintercept - cub3d->plr.y) / tan(rayAngle);

	//Calculate the increment xstep and ystep
	ystep = TILE_SIZE;
	ystep *= isRayFacingUp(rayAngle) ? -1 : 1;
	
	xstep = TILE_SIZE / tan(rayAngle);
	xstep *= (isRayFacingLeft(rayAngle) && xstep > 0) ? -1 : 1;
	xstep *= (isRayFacingRight(rayAngle) && xstep < 0) ? -1 : 1;

	float nextHorzTouchX = xintercept;
	float nextHorzTouchY = yintercept;

	//Increment xstep and ystep until we find a wall
	while (isInsideMap(nextHorzTouchX, nextHorzTouchY))
	{
		float xToCheck = nextHorzTouchX;
		float yToCheck = nextHorzTouchY + (isRayFacingUp(rayAngle) ? -1 : 0);

		if (mapHasWallAt(xToCheck, yToCheck))
		{
			//found a wall hit
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;
			horzWallTexture = getMapAt((int)floor(yToCheck / TILE_SIZE), (int)floor(xToCheck / TILE_SIZE));
			foundHorzWallHit = true;
			break;
		}
		else
		{
			nextHorzTouchX += xstep;
			nextHorzTouchY += ystep;
		}
	}

	/////////////////////////////////////////
	//VERTICAL RAY-GRID INTERSECTION CODE
	/////////////////////////////////////////
	bool foundVertWallHit = false;
	float vertWallHitX = 0;
	float vertWallHitY = 0;
	int vertWallTexture = 0;

	//Find the x-coordinate of the closest horizontal grid intersection
	xintercept = floor(cub3d->plr.x / TILE_SIZE) * TILE_SIZE;
	xintercept += isRayFacingRight(rayAngle) ? TILE_SIZE : 0;

	//Find the y-coordinate of the closest horizontal grid intersection
	yintercept = cub3d->plr.y + (xintercept - cub3d->plr.x) * tan(rayAngle);

	//Calculate the increment xstep and ystep
	xstep = TILE_SIZE;
	xstep *= isRayFacingLeft(rayAngle) ? -1 : 1;
	
	ystep = TILE_SIZE * tan(rayAngle);
	ystep *= (isRayFacingUp(rayAngle) && ystep > 0) ? -1 : 1;
	ystep *= (isRayFacingDown(rayAngle) && ystep < 0) ? -1 : 1;

	float nextVertTouchX = xintercept;
	float nextVertTouchY = yintercept;

	//Increment xstep and ystep until we find a wall
	while (isInsideMap(nextVertTouchX, nextVertTouchY))
	{
		float xToCheck = nextVertTouchX + (isRayFacingLeft(rayAngle) ? -1 : 0);
		float yToCheck = nextVertTouchY;

		if (mapHasWallAt(xToCheck, yToCheck))
		{
			//found a wall hit
			vertWallHitX = nextVertTouchX;
			vertWallHitY = nextVertTouchY;
			vertWallTexture = getMapAt((int)floor(yToCheck / TILE_SIZE), (int)floor(xToCheck / TILE_SIZE));
			foundVertWallHit = true;
			break;
		}
		else
		{
			nextVertTouchX += xstep;
			nextVertTouchY += ystep;
		}
	}

	//Calculate both horizontal and vertical hit distances and choose the smallest one
	float horzHitDistance = foundHorzWallHit ? distanceBetweenPoints(cub3d->plr.x, cub3d->plr.y, horzWallHitX, horzWallHitY)
	: FLT_MAX;
	float vertHitDistance = foundVertWallHit ? distanceBetweenPoints(cub3d->plr.x, cub3d->plr.y, vertWallHitX, vertWallHitY)
	: FLT_MAX;

	if(vertHitDistance < horzHitDistance)
	{
		rays[stripId].distance = vertHitDistance;
		rays[stripId].wallHitX = vertWallHitX;
		rays[stripId].wallHitY = vertWallHitY;
		rays[stripId].texture = vertWallTexture;
		rays[stripId].wasHitVertical = true;
		rays[stripId].rayAngle = rayAngle;
	}
	else
	{
		rays[stripId].distance = horzHitDistance;
		rays[stripId].wallHitX = horzWallHitX;
		rays[stripId].wallHitY = horzWallHitY;
		rays[stripId].texture = horzWallTexture;
		rays[stripId].wasHitVertical = false;
		rays[stripId].rayAngle = rayAngle;
	}
}

void
	castAllRays(t_cub3d *cub3d)
{

	for (int col = 0; col < NUM_RAYS; col++)
	{
		float rayAngle = cub3d->plr.rotAngle + atan((col - NUM_RAYS / 2) / DIST_PROJ_PLANE);
		castRay(cub3d, rayAngle, col);
	}
}

void
	renderMapRays(t_cub3d *cub3d)
{
	t_line line;

	for (int i = 0; i < NUM_RAYS; i++)
	{
		line = (t_line){.x0 = cub3d->plr.x * MINIMAP_SCALE_FACTOR,
				.y0 = cub3d->plr.y * MINIMAP_SCALE_FACTOR,
				.x1 = rays[i].wallHitX * MINIMAP_SCALE_FACTOR,
				.y1 = rays[i].wallHitY * MINIMAP_SCALE_FACTOR};
		drawLine(cub3d, line, BLUE);
	}
}
