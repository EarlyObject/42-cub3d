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

#include "defs.h"
#include <SDL2/SDL.h>

int isGameRunning = 0;
int ticksLastFrame = 0;

void
	exit_game(t_cub3d **p_d, int i);

void
	init_config(t_config *config)
{
	int	i;

	config->requested_width = 848;
	config->requested_height = 480;
	i = 0;
	while (i < TEXTURES)
		config->tex_path[i++] = NULL;
	config->c[TEX_NORTH] = 0xFFFFFF;
	config->c[TEX_SOUTH] = 0xCCCCCC;
	config->c[TEX_WEST] = 0xFF44FF;
	config->c[TEX_EAST] = 0x44FF44;
	config->c[TEX_SKY] = 0x33C6E3;
	config->c[TEX_FLOOR] = 0xA0764C;
	config->map = NULL;
	config->rows = 0;
	config->columns = 0;
	config->save_arg = 0;
	config->rotate_speed = .11;
	config->move_speed = .11;
	config->fov = .66;
	config->dist_proj_plane = ((config->requested_width / 2) / tan(FOV_ANGLE / 2));
	i = 0;
	while (i < C_LAST)
		config->set[i++] = 0;
}

void
	setup(t_cub3d *cub3d, t_config *config)
{
	printf("Starting SETUP\n");
	//collocate_sprites(cub3d);
	cub3d->plr.x = cub3d->config->requested_width / 2;
	cub3d->plr.y = cub3d->config->requested_height / 2;
	cub3d->plr.width = 1;
	cub3d->plr.height = 1;
	cub3d->plr.turnDrcn = 0;
	cub3d->plr.walkDrcn = 0;
	cub3d->plr.rotAngle = PI / 2;
	cub3d->plr.walkSpeed = 100;
	cub3d->plr.turnSpeed = 45 * (PI / 180);
}


void
	update(t_cub3d *cub3d)
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
	//	float deltaTime = 0.01;  //0.01 optimum?

	//Store the milliseconds of the current frame to be used in the future
	ticksLastFrame = SDL_GetTicks();

	movePlayer(cub3d, deltaTime);
	castAllRays(cub3d);
}

int
	render(t_cub3d *cub3d)
{
	clearColorBuffer(cub3d, GREEN);
	renderWallProjection(cub3d);
	renderSpriteProjection(cub3d);
	renderMapGrid(cub3d);
	renderMapRays(cub3d);
	renderMapPlayer(cub3d);
	renderMapSprites(cub3d);
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->win, cub3d->image.img_ptr, 0, 0);
	return (0);
}

void
	releaseResources(t_cub3d *cub3d)
{
	freeTextures(cub3d);
	destroyWindow();
}

int
	deal_key(int key_code, t_cub3d *cub3d)
{
	if (key_code == KEY_ESC)
	{
		isGameRunning = 0;
		exit(0);
	}

	if (key_code == KEY_W || key_code == KEY_FORWARD)
		cub3d->plr.walkDrcn = +1;
	if (key_code == KEY_S || key_code == KEY_BACKWARD)
		cub3d->plr.walkDrcn = -1;
	if (key_code == KEY_D || key_code == KEY_RIGHT)
		cub3d->plr.turnDrcn = +1;
	if (key_code == KEY_A || key_code == KEY_LEFT)
		cub3d->plr.turnDrcn = -1;
	return (0);
}

int
	key_release(int key_code, t_cub3d *cub3d)
{
	if (key_code == KEY_W || key_code == KEY_FORWARD)
		cub3d->plr.walkDrcn = 0;
	if (key_code == KEY_S || key_code == KEY_BACKWARD)
		cub3d->plr.walkDrcn = 0;
	if (key_code == KEY_D || key_code == KEY_RIGHT)
		cub3d->plr.turnDrcn = 0;
	if (key_code == KEY_A || key_code == KEY_LEFT)
		cub3d->plr.turnDrcn = 0;
	return (0);
}

int
	close_win()
{
	isGameRunning = 0;
	exit(0);
}

int
	test_loop(t_cub3d *cub3d)
{
	update(cub3d);
	render(cub3d);
	return (0);
}

int
	main(int argc, char *argv[])
{
	t_cub3d	cub3d;
	t_config config;
	int	save_option;

	if(argc == 3)
		save_option = (argc >= 2 && !ft_strncmp(argv[2], "--save", 6));
	if(argc == 2 || argc == 3 && save_option)
	{
		init_config(&config);
		if (!parse_config(&config, argv[1]))
		{
			printf("ERROR: INVALID MAP PARAMETERS.\n");
			exit(EXIT_FAILURE);
			//продумать выход с ошибкой
			//ft_exit_error(&cub3d, "ERROR: INVALID MAP PARAMETERS.\n");
		}
		cub3d.config = &config;

		setup(&cub3d, &config);
		cub3d.rays = (t_ray *)malloc(sizeof(t_ray) * (config.requested_width));



		isGameRunning = !initializeWindow(&cub3d);
		loadTextures(&cub3d);

		mlx_hook(cub3d.win, X_EVENT_KEY_PRESS, 0, &deal_key, &cub3d);
		mlx_hook(cub3d.win, X_EVENT_KEY_RELEASE, 0, &key_release, &cub3d);
		mlx_hook(cub3d.win, X_EVENT_KEY_EXIT, 0, &close_win,&cub3d);
		printf("is running = %d\n", isGameRunning);
		mlx_loop_hook(cub3d.mlx.mlx, &render, &cub3d);
		mlx_loop_hook(cub3d.mlx.mlx, &test_loop, &cub3d);
		mlx_loop(cub3d.mlx.mlx);
		return (EXIT_SUCCESS);
	}
	ft_exit_error(&cub3d, "ERROR:NO MAP SPECIFIED.\n");
}
