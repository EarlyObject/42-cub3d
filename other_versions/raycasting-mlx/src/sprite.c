/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:00:58 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/28 09:16:55 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

float
	get_angle_sprite_player(
		const t_cub3d *cub3d, int i, float angleSpritePlayer)
{
	angleSpritePlayer = cub3d->plr.rotAngle
		- atan2(cub3d->sprites[i].y - cub3d->plr.y,
			cub3d->sprites[i].x - cub3d->plr.x);
	if (angleSpritePlayer > PI)
		angleSpritePlayer -= TWO_PI;
	if (angleSpritePlayer < -PI)
		angleSpritePlayer += TWO_PI;
	angleSpritePlayer = fabs(angleSpritePlayer);
	return (angleSpritePlayer);
}

void
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
	config->num_sprites = s;
}

void
	find_sprites(t_cub3d *cub3d, t_config *config)
{
	int			i;
	int			j;
	int			x;
	int			s;

	s = 0;
	i = 0;
	while (i < config->rows)
	{
		j = 0;
		while (j < config->columns)
		{
			x = config->map[j + i * config->columns] - 48;
			if (x == 2)
			{
				//cub3d->sprites[s].x = j * TILE_SIZE + (TILE_SIZE / 2);
				cub3d->sprites[s].x = j * TILE_SIZE;
				cub3d->sprites[s].y = i * TILE_SIZE + (TILE_SIZE / 2);
				cub3d->sprites[s].texture = 6;
				s++;
			}
			j++;
		}
		i++;
	}
}

int
	find_visible_sprites(t_cub3d *cub3d, t_sprite *vsblSprites)
{
	int		numVsblSprites;
	int		i;
	float	angleSpritePlayer;

	numVsblSprites = 0;
	i = 0;
	while (i < cub3d->config->num_sprites)
	{
		angleSpritePlayer = get_angle_sprite_player(
				cub3d, i, angleSpritePlayer);
		cub3d->sprites[i].visible = false;
		if (angleSpritePlayer < (cub3d->config->fov_angle / 2) + EPSILON)
		{
			cub3d->sprites[i].visible = true;
			cub3d->sprites[i].angle = angleSpritePlayer;
			cub3d->sprites[i].distance = distanceBetweenPoints(
					cub3d->sprites[i].x, cub3d->sprites[i].y,
					cub3d->plr.x, cub3d->plr.y);
			vsblSprites[numVsblSprites] = cub3d->sprites[i];
			numVsblSprites++;
		}
		i++;
	}
	return (numVsblSprites);
}

void
	draw_sprite(t_cub3d *cub3d, t_config *config, t_sprite *sprite, int x)
{
	uint32_t	texelColor;
	float		texelWidth;
	int			y;
	int			distanceFromTop;

	texelWidth = (TEXTURE_WIDTH / sprite->width);
	sprite->texture_offset_x = (x - sprite->left_x) * texelWidth;
	y = sprite->top_y - 1;
	while (y++ < sprite->bottom_y)
	{
		if (x > 0 && x < config->width && y > 0 && y < config->height)
		{
			distanceFromTop = y + (sprite->height / 2) - (config->height / 2);
			sprite->texture_offset_y = distanceFromTop
				* (TEXTURE_HEIGHT / sprite->height);
			if (cub3d->wall.textureOffsetX > 63)
				cub3d->wall.textureOffsetX = 63;
			//printf("x = %d, texture = %d, textureOffsetX = %d, textureOffsetY = %d\n", x, sprite->texture, cub3d->wall.textureOffsetX, cub3d->wall.textureOffsetY);
			texelColor = config->wallTexture[sprite->texture]->addr[(
					TEXTURE_WIDTH * sprite->texture_offset_y)
				+ sprite->texture_offset_x];
			//texelColor = RED;
			if (sprite->distance < cub3d->rays[x].distance
				&& texelColor != 0x00FF00FF)
				drawPixel(cub3d, x, y, texelColor);
		}
	}
}
