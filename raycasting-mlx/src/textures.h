#ifndef TEXTURES_H
#define TEXTURES_H

#include <stdint.h>
#include "defs.h"
#include "upng.h"
#include "structs.h"

#define NUM_TEXTURES 13

upng_t *textures[NUM_TEXTURES];

void loadTextures(t_cub3d *cub3d);
void freeTextures();

#endif
