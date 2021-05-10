/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:44:02 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/10 16:20:58 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "defs.h"
#include "graphics.h"
#include "map.h"
#include "player.h"
#include "ray.h"
#include "wall.h"
#include "sprite.h"
#include "textures.h"
#include "../mlx/mlx.h"
#include "structs.h"

//static t_cub3d	cub3d;
int isGameRunning = 0;
int ticksLastFrame = 0;

void
	setup(t_cub3d *cub3d)
{
	//эти двое дублируются
	int textureWidth = 64;
	int textureHeight = 64;
	printf("Starting SETUP\n");
	//Asks to decode all PNG files and loads the wallTextures array
	loadTextures(cub3d);
	//create color buffer (перенес из wallRender)
	//uint32_t *wallTextureBuffer = (uint32_t *)malloc(sizeof(uint32_t) * (uint32_t)textureWidth * (uint32_t)textureHeight);//(representing textures 7.50)
	uint32_t *colorBuffer = (uint32_t *)malloc(sizeof(uint32_t) * (uint32_t)textureWidth * (uint32_t)textureHeight);//(representing textures 7.50)
	cub3d->colorBuffer = colorBuffer; //не хватает проверки


	cub3d->player.x = WINDOW_WIDTH / 2;
	cub3d->player.y = WINDOW_HEIGHT / 2;
	cub3d->player.width = 1;
	cub3d->player.height = 1;
	cub3d->player.turnDirection = 0;
	cub3d->player.walkDirection = 0;
	cub3d->player.rotationAngle = PI / 2;
	cub3d->player.walkSpeed = 100;
	cub3d->player.turnSpeed = 45 * (PI / 180);

	printf("Finishing SETUP\n"); 
}

void
	processInput(void)
{
	//SDL_Event event;
	//SDL_PollEvent(&event);
	/* switch (event.type)
	{
		case SDL_QUIT: {
			isGameRunning = false;
			break;
		}
		case SDL_KEYDOWN: {
			if(event.key.keysym.sym == SDLK_ESCAPE)
				isGameRunning = false;
			if(event.key.keysym.sym == SDLK_UP)
				player.walkDirection = +1;
			if(event.key.keysym.sym == SDLK_DOWN)
				player.walkDirection = -1;
			if(event.key.keysym.sym == SDLK_RIGHT)
				player.turnDirection = +1;
			if(event.key.keysym.sym == SDLK_LEFT)
				player.turnDirection = -1;
			break;
		}
		case SDL_KEYUP: {
			if(event.key.keysym.sym == SDLK_UP)
				player.walkDirection = 0;
			if(event.key.keysym.sym == SDLK_DOWN)
				player.walkDirection = 0;
			if(event.key.keysym.sym == SDLK_RIGHT)
				player.turnDirection = 0;
			if(event.key.keysym.sym == SDLK_LEFT)
				player.turnDirection = 0;
			break;
		}
	} */
}

void
	update(t_cub3d *cub3d)
{
	//Compute how long we have until the reach the target frame time in milliseconds
	//int timeToWait = FRAME_TIME_LENGTH - (SDL_GetTicks() - ticksLastFrame);
		int timeToWait = FRAME_TIME_LENGTH -  ticksLastFrame;
		timeToWait = 100; //придумал


	//Only delay execution if we are running too fast
	if (timeToWait > 0 && timeToWait <= FRAME_TIME_LENGTH)
	{
		//SDL_Delay(timeToWait);
	}

	//Compute the delta time to be used as an update factor when changing game objects
	//float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
		float deltaTime = ( ticksLastFrame) / 1000.0f;


	//Store the milliseconds of the current frame to be used in the future
	//ticksLastFrame = SDL_GetTicks();

	movePlayer(cub3d, deltaTime);
	castAllRays(cub3d);
}

int
	render(t_cub3d *cub3d)
{
	clearColorBuffer(cub3d, WHITE);

	//Render the wall and sprites
	//renderWallProjection(cub3d);
	//renderSpriteProjection();

	//display the minimap
	renderMapGrid(cub3d);
	renderMapRays(cub3d);
	renderMapPlayer(cub3d);
//	renderMapSprites(cub3d);

//	renderColorBuffer();
	
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->win, cub3d->image.img_ptr, 0, 0);
	return (0);
}

void
	releaseResources(void)
{
	freeTextures();
	destroyWindow();
}

int		deal_key(int key_code, t_cub3d *cub3d)
{
	if (key_code == KEY_ESC)
	{
		isGameRunning = 0;
		exit(0);
	}

	if (key_code == KEY_W || key_code == KEY_FORWARD)
		cub3d->player.walkDirection = +1;
	if (key_code == KEY_S || key_code == KEY_BACKWARD)
		cub3d->player.walkDirection = -1;
	if (key_code == KEY_D || key_code == KEY_RIGHT)
		cub3d->player.turnDirection = +1;
	if (key_code == KEY_A || key_code == KEY_LEFT)
		cub3d->player.turnDirection = -1;

	update(cub3d);
	render(cub3d);

	return (0);
}

int		key_release(int key_code, t_cub3d *cub3d)
{

	if (key_code == KEY_W || key_code == KEY_FORWARD)
		cub3d->player.walkDirection = 0;
	if (key_code == KEY_S || key_code == KEY_BACKWARD)
		cub3d->player.walkDirection = 0;
	if (key_code == KEY_D || key_code == KEY_RIGHT)
		cub3d->player.turnDirection = 0;
	if (key_code == KEY_A || key_code == KEY_LEFT)
		cub3d->player.turnDirection = 0;

	return (0);
}

int 	close_win()
{
	isGameRunning = 0;
	exit(0);
}

int
	main(void)
{
	t_cub3d	cub3d;

	isGameRunning = !initializeWindow(&cub3d);
	setup(&cub3d);

	while (isGameRunning)
	{
		//processInput();
		update(&cub3d);
		render(&cub3d);
	}
	//processInput();
	//update();
	//render(&cub3d);
	//releaseResources();
	
	mlx_hook(cub3d.win, X_EVENT_KEY_PRESS, 0, &deal_key, &cub3d);
	mlx_hook(cub3d.win, X_EVENT_KEY_RELEASE, 0, &key_release, &cub3d);
	mlx_hook(cub3d.win, X_EVENT_KEY_EXIT, 0, &close_win, &cub3d);
	printf("is running = %d\n", isGameRunning);

	mlx_loop_hook(cub3d.mlx.mlx, &render, &cub3d);
	mlx_loop(cub3d.mlx.mlx);

	return (0); //EXIT_SUCCESS
}