/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:00:58 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/13 19:26:47 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	get_sprites_dist(t_cub3d *cub3d)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub3d->config->num_sprites)
	{
		cub3d->spr_data.order[i] = (double)i;
		cub3d->spr_data.dist[i]
			= pow(cub3d->plr.posX - cub3d->config->sprites[i].x, 2);
		cub3d->spr_data.dist[i]
			+= pow(cub3d->plr.posY - cub3d->config->sprites[i].y, 2);
		i++;
	}
	j = 0;
	sort_sprites(cub3d->spr_data.order, cub3d->spr_data.dist,
		cub3d->config->num_sprites, j);
}

void
	draw_sprites(t_cub3d *cub3d)
{
	int	i;

	get_sprites_dist(cub3d);
	i = 0;
	while (i < cub3d->config->num_sprites)
	{
		calc_sprite(cub3d, i);
		draw_single_sprite(cub3d);
		i++;
	}
}

static void	init_sprites(t_cub3d *cub3d, t_config *config)
{
	int	y;
	int	x;
	int	z;

	y = 0;
	z = 0;
	while (y < config->columns)
	{
		x = 0;
		while (x < config->rows)
		{
			if (config->map[y * config->rows + x] == '2')
			{
				cub3d->spr_data.buf[z] = (double *)malloc(sizeof(double) * 2);
				cub3d->spr_data.buf[z][1] = y + 0.5;
				cub3d->spr_data.buf[z][0] = x + 0.5;
				z++;
			}
			x++;
		}
		y++;
	}
}

void
	find_sprites(t_cub3d *cub3d, t_config *config)
{
	cub3d->spr_data.dist
		= (double *)malloc(sizeof(double) * config->num_sprites);
	cub3d->spr_data.buf
		= (double **)malloc(sizeof(double *) * config->num_sprites);
	cub3d->spr_data.order
		 = (double *)malloc(sizeof(double) * config->num_sprites);
	init_sprites(cub3d, config);
}
