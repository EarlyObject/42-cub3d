#ifndef PLAYER_H
#define PLAYER_H

#include "defs.h"
#include "graphics.h"
#include "map.h"
#include "structs.h"
#include "../mlx/mlx.h"


/*typedef struct Player
{
	float x;
	float y;
	float width;
	float height;
	int turnDirection; //-1 for left, +1 for right
	int walkDirection; //-1 for back, +1 for front
	float rotationAngle;
	float walkSpeed;
	float turnSpeed;
}	player_t;*/



//extern player_t player;
void movePlayer(t_cub3d *cub3d, float deltaTime);

void renderMapPlayer(t_cub3d *cub3d);

#endif