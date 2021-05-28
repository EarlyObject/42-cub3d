/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 22:43:46 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/28 10:48:31 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	calc_hgrid_xy_steps(t_cub3d *cub3d, float rayAngle, t_ray *ray)
{
	float	xToCheck;
	float	yToCheck;

	while (isInsideMap(cub3d->config, ray->nextHorzTouchX, ray->nextHorzTouchY))
	{
		xToCheck = ray->nextHorzTouchX;
		yToCheck = ray->nextHorzTouchY;
		if (isRayFacingUp(rayAngle))
			yToCheck = ray->nextHorzTouchY + -1;
		if (mapHasWallAt(cub3d->config, xToCheck, yToCheck))
		{
			ray->horzWallHitX = ray->nextHorzTouchX;
			ray->horzWallHitY = ray->nextHorzTouchY;
			ray->horzWallTexture = getMapAt(cub3d->config,
					(int)floor(yToCheck / TILE_SIZE),
					(int)floor(xToCheck / TILE_SIZE));
			ray->foundHorzWallHit = true;
			break ;
		}
		else
		{
			ray->nextHorzTouchX += ray->xstep;
			ray->nextHorzTouchY += ray->ystep;
		}
	}
}

void
	hor_ray_grid_intersectiion(t_cub3d *cub3d, float rayAngle, t_ray *ray)
{
	ray->foundHorzWallHit = false;
	ray->horzWallHitX = 0;
	ray->horzWallHitY = 0;
	ray->horzWallTexture = 0;
	ray->yintercept = floor(cub3d->plr.y / TILE_SIZE) * TILE_SIZE;
	if (isRayFacingDown(rayAngle))
		ray->yintercept += TILE_SIZE;
	ray->xintercept = cub3d->plr.x
		+ (ray->yintercept - cub3d->plr.y) / tan(rayAngle);
	ray->ystep = TILE_SIZE;
	if (isRayFacingUp(rayAngle))
		ray->ystep *= -1;
	ray->xstep = TILE_SIZE / tan(rayAngle);
	if (isRayFacingLeft(rayAngle) && ray->xstep > 0)
		ray->xstep *= -1;
	if (isRayFacingRight(rayAngle) && ray->xstep < 0)
		ray->xstep *= -1;
	ray->nextHorzTouchX = ray->xintercept;
	ray->nextHorzTouchY = ray->yintercept;
	calc_hgrid_xy_steps(cub3d, rayAngle, ray);
}

void
	calc_vgrid_xy_steps(t_cub3d *cub3d, float rayAngle, t_ray *ray)
{
	float	xToCheck;
	float	yToCheck;

	while (isInsideMap(cub3d->config, ray->nextVertTouchX, ray->nextVertTouchY))
	{
		xToCheck = ray->nextVertTouchX;
		if (isRayFacingLeft(rayAngle))
			xToCheck = ray->nextVertTouchX + -1;
		yToCheck = ray->nextVertTouchY;
		if (mapHasWallAt(cub3d->config, xToCheck, yToCheck))
		{
			ray->vertWallHitX = ray->nextVertTouchX;
			ray->vertWallHitY = ray->nextVertTouchY;
			ray->vertWallTexture = getMapAt(cub3d->config,
					(int)floor(yToCheck / TILE_SIZE),
					(int)floor(xToCheck / TILE_SIZE));
			ray->foundVertWallHit = true;
			break ;
		}
		else
		{
			ray->nextVertTouchX += ray->xstep;
			ray->nextVertTouchY += ray->ystep;
		}
	}
}

void
	vert_ray_grid_intersection(t_cub3d *cub3d, float rayAngle, t_ray *ray)
{
	ray->foundVertWallHit = false;
	ray->vertWallHitX = 0;
	ray->vertWallHitY = 0;
	ray->vertWallTexture = 0;
	ray->xintercept = floor(cub3d->plr.x / TILE_SIZE) * TILE_SIZE;
	if (isRayFacingRight(rayAngle))
		ray->xintercept += TILE_SIZE;
	ray->yintercept = cub3d->plr.y
		+ (ray->xintercept - cub3d->plr.x) * tan(rayAngle);
	ray->xstep = TILE_SIZE;
	if (isRayFacingLeft(rayAngle))
		ray->xstep *= -1;
	ray->ystep = TILE_SIZE * tan(rayAngle);
	if (isRayFacingUp(rayAngle) && ray->ystep > 0)
		ray->ystep *= -1;
	if (isRayFacingDown(rayAngle) && ray->ystep < 0)
		ray->ystep *= -1;
	ray->nextVertTouchX = ray->xintercept;
	ray->nextVertTouchY = ray->yintercept;
	calc_vgrid_xy_steps(cub3d, rayAngle, ray);
}

void
	calc_ray_params(float rayAngle, t_ray *ray,
				float horzHitDistance, float vertHitDistance)
{
	if (vertHitDistance < horzHitDistance)
	{
		ray->distance = vertHitDistance;
		ray->wallHitX = ray->vertWallHitX;
		ray->wallHitY = ray->vertWallHitY;
		ray->texture = ray->vertWallTexture;
		ray->wasHitVertical = true;
		ray->rayAngle = rayAngle;
	}
	else
	{
		ray->distance = horzHitDistance;
		ray->wallHitX = ray->horzWallHitX;
		ray->wallHitY = ray->horzWallHitY;
		ray->texture = ray->horzWallTexture;
		ray->rayAngle = rayAngle;
		ray->wasHitVertical = false;
	}
}
