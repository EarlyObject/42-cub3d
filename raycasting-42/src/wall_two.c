/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:01:35 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/15 14:58:52 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	calc_wall_params(t_cub3d *cub3d)
{
	if (cub3d->wall.side == 0)
		cub3d->wall.perpWallDist = (cub3d->screen.mapX - cub3d->plr.posX
				+ (1 - cub3d->wall.stepX) / 2) / cub3d->wall.rayDirX;
	else
		cub3d->wall.perpWallDist = (cub3d->screen.mapY - cub3d->plr.posY
				+ (1 - cub3d->wall.stepY) / 2) / cub3d->wall.rayDirY;
	cub3d->wall.lineHeight
		= (int)(cub3d->config->height / cub3d->wall.perpWallDist);
	cub3d->wall.drawStart
		= -cub3d->wall.lineHeight / 2 + cub3d->config->height / 2;
	if (cub3d->wall.drawStart < 0)
		cub3d->wall.drawStart = 0;
	cub3d->wall.drawEnd
		= cub3d->wall.lineHeight / 2 + cub3d->config->height / 2;
	if (cub3d->wall.drawEnd >= cub3d->config->height)
		cub3d->wall.drawEnd = cub3d->config->height - 1;
}

void
	manage_walls(t_cub3d *cub3d)
{
	int	x;

	x = 0;
	while (x < cub3d->config->width)
	{
		calc_ray(cub3d, x);
		cub3d->config->hit = 0;
		calc_step_and_side_dist(cub3d);
		perform_dda(cub3d);
		calc_wall_params(cub3d);
		cub3d->wall.texNum = cub3d->config->map[cub3d->screen.mapX
			+ (cub3d->config->columns * cub3d->screen.mapY)] - '0' - 1;
		calc_wall_x(cub3d);
		cub3d->wall.texX = (uint32_t)(cub3d->wall.wallX * (double)(64));
		if (cub3d->wall.side == 0 && cub3d->wall.rayDirX > 0)
			cub3d->wall.texX = TEXTURE_WIDTH - cub3d->wall.texX - 1;
		if (cub3d->wall.side == 1 && cub3d->wall.rayDirY < 0)
			cub3d->wall.texX = TEXTURE_WIDTH - cub3d->wall.texX - 1;
		cub3d->wall.step = 1.0 * TEXTURE_HEIGHT / cub3d->wall.lineHeight;
		cub3d->wall.texPos = (cub3d->wall.drawStart - cub3d->config->height
				/ 2 + cub3d->wall.lineHeight / 2) * cub3d->wall.step;
		draw_walls(cub3d, x, cub3d->wall.drawStart, cub3d->wall.drawEnd);
		cub3d->wall.z_buffer[x] = cub3d->wall.perpWallDist;
		x++;
	}
}
