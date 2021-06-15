/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 19:59:20 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/15 14:51:20 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	draw_floor_ceiling(t_cub3d *cub3d, int start, int end, int texnum)
{
	int			x;

	while (start < end)
	{
		x = 0;
		while (x < cub3d->config->width)
		{
			draw_pixel(cub3d, x, start, cub3d->config->color[texnum]);
			x++;
		}
		start++;
	}
}
