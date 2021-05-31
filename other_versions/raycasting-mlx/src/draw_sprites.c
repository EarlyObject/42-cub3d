/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 14:58:18 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/27 20:09:43 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	render_vsbl_sprites(t_cub3d *cub3d, t_sprite *vsbl_sprites, int i)
{
	t_sprite	sprite;
	int			x;

	sprite = vsbl_sprites[i];
	sprite.height = (TILE_SIZE / sprite.distance)
		* cub3d->config->dist_proj_plane;
	sprite.width = sprite.height;
	sprite.top_y = (cub3d->config->height / 2) - (sprite.height / 2);
	if (sprite.top_y < 0)
		sprite.top_y = 0;
	sprite.bottom_y = (cub3d->config->height / 2) + (sprite.height / 2);
	if (sprite.bottom_y > cub3d->config->height)
		sprite.bottom_y = cub3d->config->height;
	sprite.angle = atan2(sprite.y - cub3d->plr.y, sprite.x - cub3d->plr.x)
		- cub3d->plr.rotAngle;
	sprite.x = tan(sprite.angle) * cub3d->config->dist_proj_plane;
	sprite.left_x = (cub3d->config->width / 2) + sprite.x - (sprite.width / 2);
	sprite.right_x = sprite.left_x + sprite.width;
	x = (roundf(sprite.left_x));
	//printf("x = %d, sprite.left_x = %f, sprite.right_x = %f\n", x, sprite.left_x, sprite.right_x);
	while (x < sprite.right_x)
	{
		draw_sprite(cub3d, cub3d->config, &sprite, x);
		x++;
	}
}

void
	swap_sprites(t_sprite *visibleSprites, t_sprite *temp, int i, int j)
{
	(*temp) = visibleSprites[i];
	visibleSprites[i] = visibleSprites[j];
	visibleSprites[j] = (*temp);
}

void
	renderSpriteProjection(t_cub3d *cub3d, t_config *config)
{
	t_sprite	*visibleSprites;
	t_sprite	temp;
	int			numVisibleSprites;
	int			i;
	int			j;

	visibleSprites = config->visibleSprites;
	numVisibleSprites = find_visible_sprites(cub3d, visibleSprites);
	i = 0;
	while (i < numVisibleSprites - 1)
	{
		j = 1;
		while (j < numVisibleSprites)
		{
			if (visibleSprites[i].distance < visibleSprites[j].distance)
				swap_sprites(visibleSprites, &temp, i, j);
			j++;
		}
		i++;
	}
	i = -1;
	while (i++ < numVisibleSprites)
	{
		render_vsbl_sprites(cub3d, visibleSprites, i);
	}
}
