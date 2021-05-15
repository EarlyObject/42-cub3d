/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:00:58 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/14 14:00:59 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

#define NUM_SPRITES 6

static sprite_t sprites[NUM_SPRITES] = {
	{ .x = 640, .y = 630, .texture =  8 }, // barrel 
	{ .x = 660, .y = 690, .texture =  8 }, // barrel 
	{ .x = 250, .y = 600, .texture = 10 }, // table 
	{ .x = 250, .y = 600, .texture =  9 }, // light 
	{ .x = 300, .y = 400, .texture = 11 }, // guard
	{ .x =  90, .y = 100, .texture = 12 } // armor
};

void
	renderMapSprites(t_cub3d *cub3d)
{
	int			i;
	uint32_t	color;

	i = 0;
	while (i < NUM_SPRITES)
	{
		color = 0xFF444444;
		if (sprites[i].visible)
			color = 0xFF00FFFF;
		drawRect(
			cub3d,
			sprites[i].x * MINIMAP_SCALE_FACTOR,
			sprites[i].y * MINIMAP_SCALE_FACTOR,
			2,
			2,
			color);
		i++;
	}
}

int
	find_visible_sprites(t_cub3d *cub3d, sprite_t *vsblSprites)
{
	int		numVsblSprites;
	int		i;
	float	angleSpritePlayer;

	numVsblSprites = 0;
	i = 0;
	while (i < NUM_SPRITES)
	{
		angleSpritePlayer = cub3d->plr.rotAngle - atan2(sprites[i].y - cub3d->plr.y, sprites[i].x - cub3d->plr.x);
		if (angleSpritePlayer > PI)
			angleSpritePlayer -= TWO_PI;
		if (angleSpritePlayer < -PI)
			angleSpritePlayer += TWO_PI;
		angleSpritePlayer = fabs(angleSpritePlayer);
		//If sprite angle is less than half the FOV plas a small error magrin
		const float EPSILON = 0.2;
		if (angleSpritePlayer < (FOV_ANGLE / 2) + EPSILON)
		{
			sprites[i].visible = true;
			sprites[i].angle = angleSpritePlayer;
			sprites[i].distance = distanceBetweenPoints(sprites[i].x, sprites[i].y, cub3d->plr.x, cub3d->plr.y);
			vsblSprites[numVsblSprites] = sprites[i];//cheknut'
			numVsblSprites++;
		}
		else
			sprites[i].visible = false;
		i++;
	}
	return (numVsblSprites);
}

void
	render_visible_sprites(t_cub3d *cub3d, const sprite_t *visibleSprites, sprite_t *sprite, int i)
{
	(*sprite) = visibleSprites[i];

	//Calculate the sprite projected height and width (the same, as sprites are squared)
	float spriteHeight = (TILE_SIZE / (*sprite).distance) * DIST_PROJ_PLANE;
	float spriteWidth = spriteHeight;

	//Calculate sprite top Y
	float spriteTopY = (WINDOW_HEIGHT / 2) - (spriteHeight / 2);
	spriteTopY = (spriteTopY < 0) ? 0 : spriteTopY;

	//Calculate sprite bottom Y
	float spriteBottomY = (WINDOW_HEIGHT / 2) + (spriteHeight / 2);
	spriteBottomY = (spriteBottomY > WINDOW_HEIGHT) ? WINDOW_HEIGHT : spriteBottomY;

	//Calculate the sprite X position in the projection plane
	float spriteAngle = atan2((*sprite).y - cub3d->plr.y, (*sprite).x - cub3d->plr.x) - cub3d->plr.rotAngle;
	float spriteScreenPosX = tan(spriteAngle) * DIST_PROJ_PLANE;

	//Sprite left x
	float spriteLeftX = (WINDOW_WIDTH / 2) + spriteScreenPosX - (spriteWidth / 2);

	//Sprite right x
	float spriteRightX = spriteLeftX + spriteWidth;

	//loop all the x values
	for (int x = spriteLeftX; x < spriteRightX; x++)
	{
		float texelWidth = (TEXTURE_WIDTH / spriteWidth);
		int textureOffsetX = (x - spriteLeftX) * texelWidth;

		//loop all the y values
		for (int y = spriteTopY; y < spriteBottomY; y++)
		{
			if (x > 0 && x < WINDOW_WIDTH && y > 0 && y < WINDOW_HEIGHT)
			{
				int distanceFromTop = y + (spriteHeight / 2) - (WINDOW_HEIGHT / 2);
				int textureOffsetY = distanceFromTop * (TEXTURE_HEIGHT / spriteHeight);
				uint32_t *spriteTextureBuffer = cub3d->wallTexture[(*sprite).texture]->addr;
				uint32_t texelColor = spriteTextureBuffer[(TEXTURE_WIDTH * textureOffsetY) + textureOffsetX];
				if ((*sprite).distance < rays[x].distance && texelColor != 0x00FF00FF)
						drawPixel(cub3d, x, y, texelColor);
			}
		}
	}
}

void
	renderSpriteProjection(t_cub3d *cub3d)
{
	sprite_t	visibleSprites[NUM_SPRITES];
	sprite_t	sprite;
	sprite_t	temp;
	int			numVisibleSprites;
	int			i;
	int			j;

	numVisibleSprites = find_visible_sprites(cub3d, visibleSprites);
	i = 0;
	while (i < numVisibleSprites - 1)
	{
		j = 1;
		while (j < numVisibleSprites)
		{
			if (visibleSprites[i].distance < visibleSprites[j].distance)
			{
				temp = visibleSprites[i];
				visibleSprites[i] = visibleSprites[j];
				visibleSprites[j] = temp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < numVisibleSprites)
	{
		render_visible_sprites(cub3d, visibleSprites, &sprite, i);
		i++;
	}
}
