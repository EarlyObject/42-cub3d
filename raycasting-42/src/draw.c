/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 15:25:01 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/25 21:35:10 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
drawPixel(t_cub3d *cub3d, int x, int y, uint32_t color)
{
	if (x >= 0 && x < cub3d->config->width
		&& y >= 0 && y < cub3d->config->height)
		cub3d->image.addr[(cub3d->config->width * y) + x] = color;
}

void
	drawRect(t_cub3d *cub3d, t_rectangle rectangle, uint32_t color)
{
	int	i;
	int	j;

	i = rectangle.x;
	while (i <= (rectangle.x + rectangle.width))
	{
		j = rectangle.y;
		while (j <= (rectangle.y + rectangle.height))
		{
			drawPixel(cub3d, i, j, color);
			j++;
		}
		i++;
	}
}

void
draw_line(t_cub3d *cub3d, int x, int y, int y1, uint32_t color)
{
	while (y < y1)
	{
		drawPixel(cub3d, x, y, color);
		y++;
	}

}


