/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:00:27 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/27 20:26:26 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

bool
	mapHasWallAt(t_config *config, float x, float y)
{
	int	mapGridIndexX;
	int	mapGridIndexY;
	int	z;

	if (x < 0 || x >= config->width || y < 0
		|| y >= config->height)
		return (true);
	mapGridIndexX = floor(x / TILE_SIZE);
	mapGridIndexY = floor(y / TILE_SIZE);
	z = config->map[mapGridIndexX + mapGridIndexY * config->columns] - 48;
	return (z == 1);
}

bool
	isInsideMap(t_config *config, float x, float y)
{
	return (x >= 0 && x <= config->columns * TILE_SIZE
		&& y >= 0 && y <= config->rows * TILE_SIZE);
}

int
	getMapAt(t_config *config, int i, int j)
{
	int	x;
	int	addr;

	addr = j + i * config->columns;
	if (addr >= config->width * config->height)
		addr = config->width * config->height - 1;
	x = config->map[addr] - 48;
	if (x == 30 || x == 35 || x == 39 || x == 21)
		x = 0;
	return (x);
}

void
	renderMapGrid(t_cub3d *cub3d)
{
	int			i;
	int			j;
	int			tileX;
	int			tileY;
	uint32_t	tileColor;

	i = -1;
	while (i++ < cub3d->config->rows - 1)
	{
		j = -1;
		while (j++ < cub3d->config->columns - 1)
		{
			tileX = j * TILE_SIZE;
			tileY = i * TILE_SIZE;
			if (getMapAt(cub3d->config, i, j) == 1)
				tileColor = WHITE;
			else
				tileColor = BLACK;
			cub3d->rectangle = (t_rectangle){.x = tileX * MINIMAP_SCALE_FACTOR,
				.y = tileY * MINIMAP_SCALE_FACTOR,
				.width = TILE_SIZE * MINIMAP_SCALE_FACTOR,
				.height = TILE_SIZE * MINIMAP_SCALE_FACTOR};
			drawRect(cub3d, cub3d->rectangle, tileColor);
		}
	}
}
