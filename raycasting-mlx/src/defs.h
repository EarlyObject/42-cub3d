/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:44:32 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/13 09:37:27 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <SDL2/SDL.h>
# include <limits.h>
# include "structs.h"
# include "../mlx/mlx.h"
# include "upng.h"

# define PI 3.14159265
# define TWO_PI 6.28318530
# define TILE_SIZE 64
# define MINIMAP_SCALE_FACTOR 0.2
//#define WINDOW_WIDTH 1280
//#define WINDOW_HEIGHT 800

# define MAP_NUM_ROWS 13
# define MAP_NUM_COLS 20
# define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
# define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

# define FOV_ANGLE (60 * (PI / 180))
# define NUM_RAYS WINDOW_WIDTH
# define DIST_PROJ_PLANE ((WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2))
# define FPS 30
# define FRAME_TIME_LENGTH (1000 / FPS)

//graphics
int
	initializeWindow(t_cub3d *cub3d);
void
	destroyWindow(void);
int
	clearColorBuffer(t_cub3d *cub3d, uint32_t color);
void renderColorBuffer(void);
void drawPixel(t_cub3d *cub3d, int x, int y, uint32_t color);
void drawRect(t_cub3d *cub3d, int x, int y, int width, int height, uint32_t color);
void drawLine(t_cub3d *cub3d, int x0, int y0, int x1, int y1, uint32_t color);

//map
bool mapHasWallAt(float x, float y);
bool isInsideMap(float x, float y);
void renderMapGrid(t_cub3d *cub3d);
int getMapAt(int i, int j);

//player
void movePlayer(t_cub3d *cub3d, float deltaTime);
//void movePlayer(t_cub3d *cub3d);
void renderMapPlayer(t_cub3d *cub3d);

//ray
extern ray_t rays[NUM_RAYS];

bool isRayFacingUp(float angle);
bool isRayFacingDown(float angle);
bool isRayFacingLeft(float angle);
bool isRayFacingRight(float angle);
void castRay(t_cub3d *cub3d, float rayAngle, int stripId);
void castAllRays(t_cub3d *cub3d);
void renderMapRays(t_cub3d *cub3d);

//sprite
void renderSpriteProjection(t_cub3d *cub3d);
void renderMapSprites(t_cub3d *cub3d);

//textures
//upng_t *textures[NUM_TEXTURES];

void loadTextures(t_cub3d *cub3d);
void freeTextures();

//utils
void normalizeAngle(float *angle);
float distanceBetweenPoints(float x1, float y1, float x2, float y2);

//wall
void renderWallProjection(t_cub3d *cub3d);

#endif