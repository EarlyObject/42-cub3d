#include "structs.h"
#include "defs.h"

void
	movePlayer(t_cub3d *cub3d, float deltaTime)
{
	cub3d->player.rotationAngle += cub3d->player.turnDirection * cub3d->player.turnSpeed * deltaTime;
	normalizeAngle(&cub3d->player.rotationAngle);
	float moveStep = cub3d->player.walkDirection * cub3d->player.walkSpeed * deltaTime;
	float newPlayerX = cub3d->player.x + cos(cub3d->player.rotationAngle) * moveStep;
	float newPlayerY = cub3d->player.y + sin(cub3d->player.rotationAngle) * moveStep;

	//perform wall collision
	if (!mapHasWallAt(newPlayerX, newPlayerY))
	{
		cub3d->player.x = newPlayerX;
		cub3d->player.y = newPlayerY;
	}
}

void
	renderMapPlayer(t_cub3d *cub3d)
{
	drawRect(
		cub3d,
		cub3d->player.x * MINIMAP_SCALE_FACTOR,
		cub3d->player.y * MINIMAP_SCALE_FACTOR,
		cub3d->player.width * MINIMAP_SCALE_FACTOR,
		cub3d->player.height * MINIMAP_SCALE_FACTOR,
		0xFFFFFFFF
	);
	drawLine(
			cub3d,
			MINIMAP_SCALE_FACTOR * cub3d->player.x,
			MINIMAP_SCALE_FACTOR * cub3d->player.y,
			MINIMAP_SCALE_FACTOR * cub3d->player.x + cos(cub3d->player.rotationAngle) * 40,
			MINIMAP_SCALE_FACTOR * cub3d->player.y + sin(cub3d->player.rotationAngle) * 40,
			RED
	);
}