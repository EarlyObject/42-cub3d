/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:00:52 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/28 10:48:58 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

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
	if (ray->foundHorzWallHit)
		horzHitDistance = distanceBetweenPoints(
				cub3d->plr.x, cub3d->plr.y, ray->horzWallHitX,
				ray->horzWallHitY);
	else
		horzHitDistance = FLT_MAX;
	if (ray->foundVertWallHit)
		vertHitDistance = distanceBetweenPoints(cub3d->plr.x,
				cub3d->plr.y, ray->vertWallHitX, ray->vertWallHitY);
	else
		vertHitDistance = FLT_MAX;
	calc_ray_params(rayAngle, ray, horzHitDistance, vertHitDistance);
}

void
	castAllRays(t_cub3d *cub3d)
{
	float	rayAngle;
	int		num_rays;
	int		col;

	col = 0;
	num_rays = cub3d->config->width;
	while (col < num_rays)
	{
		rayAngle = cub3d->plr.rotAngle
			+ atan((col - num_rays / 2) / cub3d->config->dist_proj_plane);
		castRay(cub3d, rayAngle, col);
		col++;
	}
}

void
	renderMapRays(t_cub3d *cub3d)
{
	t_line	line;
	int		num_rays;
	int		i;

	i = 0;
	num_rays = cub3d->config->width;
	while (i < num_rays)
	{
		line = (t_line){.x0 = cub3d->plr.x * MINIMAP_SCALE_FACTOR,
			.y0 = cub3d->plr.y * MINIMAP_SCALE_FACTOR,
			.x1 = cub3d->rays[i].wallHitX * MINIMAP_SCALE_FACTOR,
			.y1 = cub3d->rays[i].wallHitY * MINIMAP_SCALE_FACTOR};
		drawLine(cub3d, line, BLUE);
		i++;
	}
}
