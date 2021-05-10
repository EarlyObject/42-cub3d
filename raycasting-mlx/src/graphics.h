#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdbool.h>
#include <stdint.h>
#include<SDL2/SDL.h>
#include "defs.h"
#include "structs.h"
#include "../mlx/mlx.h"


int initializeWindow(t_cub3d *cub3d);
void destroyWindow(void);
int clearColorBuffer(t_cub3d *cub3d, uint32_t color);
void renderColorBuffer(void);
void drawPixel(t_cub3d *cub3d, int x, int y, uint32_t color);
void drawRect(t_cub3d *cub3d, int x, int y, int width, int height, uint32_t color);
void drawLine(t_cub3d *cub3d, int x0, int y0, int x1, int y1, uint32_t color);

#endif