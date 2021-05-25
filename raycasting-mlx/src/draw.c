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
	drawLine(t_cub3d *cub3d, t_line line, uint32_t color)
{
	int		i;
	float	xIncrement;
	float	yIncrement;
	float	currentX;
	float	currentY;

	if (abs(get_delta(line.x1, line.x0)) >= abs(get_delta(line.y1, line.y0)))
		line.longestSideLength = abs(get_delta(line.x1, line.x0));
	else
		line.longestSideLength = abs(get_delta(line.y1, line.y0));
	xIncrement = get_delta(line.x1, line.x0) / (float)line.longestSideLength;
	yIncrement = get_delta(line.y1, line.y0) / (float)line.longestSideLength;
	currentX = line.x0;
	currentY = line.y0;
	i = 0;
	while (i < line.longestSideLength)
	{
		drawPixel(cub3d, round(currentX), round(currentY), color);
		currentX += xIncrement;
		currentY += yIncrement;
		i++;
	}
}

void
	drawPixel(t_cub3d *cub3d, int x, int y, uint32_t color)
{
	if (x >= 0 && x < cub3d->config->width
		&& y >= 0 && y < cub3d->config->height)
		cub3d->image.addr[(cub3d->config->width * y) + x] = color;
}
