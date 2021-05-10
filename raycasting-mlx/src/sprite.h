#ifndef SPRITE_H
#define SPRITE_H

#include "defs.h"
#include "graphics.h"
#include "player.h"
#include "textures.h"
#include "structs.h"

typedef struct {
	float x;
	float y;
	float distance;
	float angle;
	bool visible;
	int texture;
} sprite_t;

void renderSpriteProjection(t_cub3d *cub3d);
void renderMapSprites(t_cub3d *cub3d);

#endif