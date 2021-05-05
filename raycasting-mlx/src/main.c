/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:44:02 by asydykna          #+#    #+#             */
/*   Updated: 2021/04/30 12:42:25 by asydykna         ###   ########.fr       */
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

bool isGameRunning = false;
int ticksLastFrame = 0;

void
	setup(void)
{
	//Asks uPNG library to decode all PNG files and loads the wallTextures array
	loadTextures();
}

void
	processInput(void)
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
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
	}
}

void
	update()
{
	//Compute how long we have until the reach the target frame time in milliseconds
	int timeToWait = FRAME_TIME_LENGTH - (SDL_GetTicks() - ticksLastFrame);

	//Only delay execution if we are running too fast
	if (timeToWait > 0 && timeToWait <= FRAME_TIME_LENGTH)
	{
		SDL_Delay(timeToWait);
	}

	//Compute the delta time to be used as an update factor when changing game objects
	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

	//Store the milliseconds of the current frame to be used in the future
	ticksLastFrame = SDL_GetTicks();

	movePlayer(deltaTime);
	castAllRays();
}

void
	render()
{
	clearColorBuffer(0xFF000000);
	//Render the wall and sprites
	renderWallProjection();
	renderSpriteProjection();

	//display the minimap
	renderMapGrid();
	renderMapRays();
	renderMapPlayer();
	renderMapSprites();

	renderColorBuffer();
}

void
	releaseResources(void)
{
	freeTextures();
	destroyWindow();
}

int
	main(void)
{
	isGameRunning = initializeWindow();
	setup();
	while (isGameRunning)
	{
		processInput();
		update();
		render();
	}
	releaseResources();
	return (0); //EXIT_SUCCESS
}