/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:00:58 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/16 22:28:30 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

#define NUM_SPRITES 3

/*t_sprite	sprites[NUM_SPRITES] = {
	{.x = 640, .y = 630, .texture = 8},
	{.x = 660, .y = 690, .texture = 8},
	{.x = 250, .y = 600, .texture = 10},
	{.x = 250, .y = 600, .texture = 9},
	{.x = 300, .y = 400, .texture = 11},
	{.x = 90, .y = 100, .texture = 12}
	};*/

void
	renderMapSprites(t_cub3d *cub3d)
{
	int			i;
	int			j;
	int			x;
	uint32_t	color;
	t_rectangle	rectangle;
	int w = cub3d->config->requested_width / cub3d->config->columns;
	int h = cub3d->config->requested_height / cub3d->config->rows;

	i = -1;
	while (i++ < cub3d->config->rows - 1)
	{
		j = -1;
		while (j++ < cub3d->config->columns - 1)
		{
			x = cub3d->config->map[j + i * cub3d->config->columns] - 48;
			color = 0xFF00FFFF;
			if (x == 2)
			{
				/*rectangle = (t_rectangle){.x = j * w * MINIMAP_SCALE_FACTOR,
						.y = i * h * MINIMAP_SCALE_FACTOR, .width = 2, .height = 2};*/
				rectangle = (t_rectangle){.x = j * w * MINIMAP_SCALE_FACTOR,
						.y = i * h * MINIMAP_SCALE_FACTOR, .width = 2, .height = 2};
				drawRect(cub3d, rectangle, color);
			}
		}
	}
}

float
	get_angle_sprite_player(
		const t_cub3d *cub3d, int i, float angleSpritePlayer)
{
	angleSpritePlayer = cub3d->plr.rotAngle
		- atan2(cub3d->sprites[i]->y - cub3d->plr.y, cub3d->sprites[i]->x - cub3d->plr.x);
	if (angleSpritePlayer > PI)
		angleSpritePlayer -= TWO_PI;
	if (angleSpritePlayer < -PI)
		angleSpritePlayer += TWO_PI;
	angleSpritePlayer = fabs(angleSpritePlayer);
	return (angleSpritePlayer);
}

void
	find_sprites(t_cub3d *cub3d, t_config *config)
{
	int			i;
	int			j;
	int			x;
	int			s;

	s = 0;
	i = -1;
	while (i++ < cub3d->config->rows - 1)
	{
		j = -1;
		while (j++ < cub3d->config->columns - 1)
		{
			x = cub3d->config->map[j + i * cub3d->config->columns] - 48;
			if (x == 2)
			{
				cub3d->sprites[s] = (t_sprite *) malloc(sizeof(t_sprite*));
				cub3d->sprites[s]->x = j * TILE_SIZE;
				cub3d->sprites[s]->y = i * TILE_SIZE;
				cub3d->sprites[s]->texture = 6;
				s++;
			}
		}
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
	while (i < NUM_SPRITES)
	{
		angleSpritePlayer = get_angle_sprite_player(
				cub3d, i, angleSpritePlayer);
		cub3d->sprites[i]->visible = false;
		if (angleSpritePlayer < (FOV_ANGLE / 2) + EPSILON)
		{
			cub3d->sprites[i]->visible = true;
			cub3d->sprites[i]->angle = angleSpritePlayer;
			cub3d->sprites[i]->distance = distanceBetweenPoints(
					cub3d->sprites[i]->x, cub3d->sprites[i]->y, cub3d->plr.x, cub3d->plr.y);
			vsblSprites[numVsblSprites] = *cub3d->sprites[i];
			numVsblSprites++;
		}
		i++;
	}
	return (numVsblSprites);
}

void
	draw_sprite(t_cub3d *cub3d, t_sprite *sprite, int x)
{
	uint32_t	texelColor;
	float		texelWidth;
	int			y;
	int			distanceFromTop;

	texelWidth = (TEXTURE_WIDTH / sprite->width);
	sprite->texture_offset_x = (x - sprite->left_x) * texelWidth;
	y = sprite->top_y;
	while (y < sprite->bottom_y)
	{
		if (x > 0 && x < cub3d->config->requested_width && y > 0 && y < cub3d->config->requested_height)
		{
			distanceFromTop
					= y + (sprite->height / 2) - (cub3d->config->requested_height / 2);
			sprite->texture_offset_y
					= distanceFromTop * (TEXTURE_HEIGHT / sprite->height);
			texelColor = cub3d->wallTexture[sprite->texture]
					->addr[(TEXTURE_WIDTH * sprite->texture_offset_y)
						   + sprite->texture_offset_x];
			if (sprite->distance < cub3d->rays[x].distance && texelColor != 0x00FF00FF)

					drawPixel(cub3d, x, y, texelColor);
		}
		y++;
	}
}
