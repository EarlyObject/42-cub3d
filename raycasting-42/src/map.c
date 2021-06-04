/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:00:27 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/05 14:45:35 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	draw_map_sprites(t_cub3d *cub3d, int i, int j)
{
	uint32_t	color;
	t_rectangle	rectangle;
	int			x;
	int			w;
	int			h;

	w = cub3d->config->width / cub3d->config->columns;
	h = cub3d->config->height / cub3d->config->rows;
	x = cub3d->config->map[j + i * cub3d->config->columns] - 48;
	color = 0xFF00FFFF;
	if (x == 2)
	{
		(rectangle) = (t_rectangle){.x = j * w * MINIMAP_SCALE_FACTOR,
			.y = i * h * MINIMAP_SCALE_FACTOR, .width = 2, .height = 2};
		drawRect(cub3d, rectangle, color);
	}
}

void
	renderMapSprites(t_cub3d *cub3d)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub3d->config->rows)
	{
		j = 0;
		while (j < cub3d->config->columns)
		{
			draw_map_sprites(cub3d, i, j);
			j++;
		}
		i++;
	}
}

void
	renderMapPlayer(t_cub3d *cub3d)
{
	t_rectangle	rectangle;

	rectangle = (t_rectangle){.x = (int)(cub3d->plr.posX
			* cub3d->config->tile_width * MINIMAP_SCALE_FACTOR),
		.y = (int)(cub3d->plr.posY * cub3d->config->tile_height
			* MINIMAP_SCALE_FACTOR),
		.width = (int)(5 * MINIMAP_SCALE_FACTOR),
		.height = (int)(5 * MINIMAP_SCALE_FACTOR)};
	drawRect(cub3d, rectangle, RED);
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
			tileX = (int)(round)(j * cub3d->config->tile_width);
			tileY = (int)(round)(i * cub3d->config->tile_height);
			if (getMapAt(cub3d->config, i, j) == 1)
				tileColor = WHITE;
			else
				tileColor = BLACK;
			cub3d->rectangle = (t_rectangle){.x = tileX * MINIMAP_SCALE_FACTOR,
				.y = tileY * MINIMAP_SCALE_FACTOR,
				.width = cub3d->config->tile_width * MINIMAP_SCALE_FACTOR,
				.height = cub3d->config->tile_height * MINIMAP_SCALE_FACTOR};
			drawRect(cub3d, cub3d->rectangle, tileColor);
		}
	}
}
