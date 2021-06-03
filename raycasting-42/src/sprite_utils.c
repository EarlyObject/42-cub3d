/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 15:01:58 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/04 15:05:44 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

float
	dist_btw_pts(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void
	swap_sprites(t_sprite *visibleSprites, t_sprite *temp, int i, int j)
{
	(*temp) = visibleSprites[i];
	visibleSprites[i] = visibleSprites[j];
	visibleSprites[j] = (*temp);
}

void
	sort_sprites(t_cub3d *cub3d, t_config *config)
{
	int			i;
	int			j;
	t_sprite	temp;

	i = 0;
	while (i < cub3d->config->num_sprites)
	{
		config->sprites[i].dist = dist_btw_pts(config->sprites[i].x,
				config->sprites[i].y, cub3d->plr.posX, cub3d->plr.posY);
		i++;
	}
	i = 0;
	while (i < cub3d->config->num_sprites - 1)
	{
		j = 1;
		while (j < cub3d->config->num_sprites)
		{
			if (cub3d->config->sprites[i].dist < cub3d->config->sprites[j].dist)
			{
				swap_sprites(cub3d->config->sprites, &temp, i, j);
			}
			j++;
		}
		i++;
	}
}

int
	count_sprites(t_config *config)
{
	int			i;
	int			j;
	int			x;
	int			s;

	i = 0;
	s = 0;
	while (i < config->rows)
	{
		j = 0;
		while (j < config->columns)
		{
			x = config->map[j + i * config->columns] - 48;
			if (x == 2)
				s++;
			j++;
		}
		i++;
	}
	return (s);
}
