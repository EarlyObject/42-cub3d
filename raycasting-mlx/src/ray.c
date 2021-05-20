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

//t_ray rays[NUM_RAYS];

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
	calc_hgrid_xy_steps(t_cub3d *cub3d, float rayAngle, t_ray *ray)
{
	while (isInsideMap(cub3d->config, ray->nextHorzTouchX, ray->nextHorzTouchY))
	{
		float xToCheck = ray->nextHorzTouchX;
		float yToCheck = ray->nextHorzTouchY + (isRayFacingUp(rayAngle) ? -1 : 0);

		if (mapHasWallAt(cub3d->config, xToCheck, yToCheck))
		{
			ray->horzWallHitX = ray->nextHorzTouchX;
			ray->horzWallHitY = ray->nextHorzTouchY;
			ray->horzWallTexture = getMapAt(cub3d->config, (int)floor(yToCheck / TILE_SIZE), (int)floor(xToCheck / TILE_SIZE));
			ray->foundHorzWallHit = true;
			break;
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
	ray->yintercept += isRayFacingDown(rayAngle) ? TILE_SIZE : 0;
	ray->xintercept = cub3d->plr.x + (ray->yintercept - cub3d->plr.y) / tan(rayAngle);
	ray->ystep = TILE_SIZE;
	ray->ystep *= isRayFacingUp(rayAngle) ? -1 : 1;
	ray->xstep = TILE_SIZE / tan(rayAngle);
	ray->xstep *= (isRayFacingLeft(rayAngle) && ray->xstep > 0) ? -1 : 1;
	ray->xstep *= (isRayFacingRight(rayAngle) && ray->xstep < 0) ? -1 : 1;
	ray->nextHorzTouchX = ray->xintercept;
	ray->nextHorzTouchY = ray->yintercept;
	calc_hgrid_xy_steps(cub3d, rayAngle, ray);
}

void
	calc_vgrid_xy_steps(t_cub3d *cub3d, float rayAngle, t_ray *ray)
{
	while (isInsideMap(cub3d->config, ray->nextVertTouchX, ray->nextVertTouchY))
	{
		float xToCheck = ray->nextVertTouchX + (isRayFacingLeft(rayAngle) ? -1 : 0);
		float yToCheck = ray->nextVertTouchY;
		if (mapHasWallAt(cub3d->config, xToCheck, yToCheck))
		{
			ray->vertWallHitX = ray->nextVertTouchX;
			ray->vertWallHitY = ray->nextVertTouchY;
			ray->vertWallTexture = getMapAt(
				cub3d->config,
			 (int)floor(yToCheck / TILE_SIZE),
			 (int)floor(xToCheck / TILE_SIZE));
			ray->foundVertWallHit = true;
			break;
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
	ray->xintercept += isRayFacingRight(rayAngle) ? TILE_SIZE : 0;
	ray->yintercept = cub3d->plr.y + (ray->xintercept - cub3d->plr.x) * tan(rayAngle);
	ray->xstep = TILE_SIZE;
	ray->xstep *= isRayFacingLeft(rayAngle) ? -1 : 1;
	ray->ystep = TILE_SIZE * tan(rayAngle);
	ray->ystep *= (isRayFacingUp(rayAngle) && ray->ystep > 0) ? -1 : 1;
	ray->ystep *= (isRayFacingDown(rayAngle) && ray->ystep < 0) ? -1 : 1;
	ray->nextVertTouchX = ray->xintercept;
	ray->nextVertTouchY = ray->yintercept;
	calc_vgrid_xy_steps(cub3d, rayAngle, ray);
}

void
	calc_ray_params(float rayAngle, t_ray *ray, float horzHitDistance, float vertHitDistance)
{
	if(vertHitDistance < horzHitDistance)
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

void
	castRay(t_cub3d *cub3d, float rayAngle, int stripId)
{
	t_ray	*ray;
	float	horzHitDistance;
	float	vertHitDistance;

	ray = &cub3d->rays[stripId];
	normalizeAngle(&rayAngle);

	hor_ray_grid_intersectiion(cub3d, rayAngle, ray);
	vert_ray_grid_intersection(cub3d, rayAngle, ray);

	//Calculate both horizontal and vertical hit distances and choose the smallest one
	if (ray->foundHorzWallHit)
		horzHitDistance = distanceBetweenPoints(cub3d->plr.x, cub3d->plr.y, ray->horzWallHitX, ray->horzWallHitY);
	else
		horzHitDistance = FLT_MAX;
	if (ray->foundVertWallHit)
		vertHitDistance = distanceBetweenPoints(cub3d->plr.x, cub3d->plr.y, ray->vertWallHitX, ray->vertWallHitY);
	else
		vertHitDistance = FLT_MAX;
	calc_ray_params(rayAngle, ray, horzHitDistance, vertHitDistance);
}

void
	castAllRays(t_cub3d *cub3d)
{
	int num_rays;

	num_rays = cub3d->config->width;
	for (int col = 0; col < num_rays; col++)
		{
		float rayAngle = cub3d->plr.rotAngle + atan((col - num_rays / 2) / cub3d->config->dist_proj_plane);
			castRay(cub3d, rayAngle, col);
	}
}

void
	renderMapRays(t_cub3d *cub3d)
{
	t_line line;
	int 	num_rays;

	num_rays = cub3d->config->width;
	for (int i = 0; i < num_rays; i++)
		{
		line = (t_line){.x0 = cub3d->plr.x * MINIMAP_SCALE_FACTOR,
				.y0 = cub3d->plr.y * MINIMAP_SCALE_FACTOR,
				.x1 = cub3d->rays[i].wallHitX * MINIMAP_SCALE_FACTOR,
				.y1 = cub3d->rays[i].wallHitY * MINIMAP_SCALE_FACTOR};
		drawLine(cub3d, line, BLUE);
	}
}
