#ifndef RAY_H
#define RAY_H

#include <stdbool.h>
#include <limits.h>
#include "defs.h"
#include "graphics.h"
#include "player.h"
#include "structs.h"


typedef struct {
	float rayAngle;
	float wallHitX;
	float wallHitY;
	float distance;
	bool wasHitVertical;
	int texture;
} ray_t;

extern ray_t rays[NUM_RAYS];

bool isRayFacingUp(float angle);
bool isRayFacingDown(float angle);
bool isRayFacingLeft(float angle);
bool isRayFacingRight(float angle);
void castRay(t_cub3d *cub3d, float rayAngle, int stripId);
void castAllRays(t_cub3d *cub3d);
void renderMapRays(t_cub3d *cub3d);

#endif