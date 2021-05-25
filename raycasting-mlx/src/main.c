/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:44:02 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/25 22:12:39 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"
#include <SDL2/SDL.h>

int ticksLastFrame = 0;

void
	update(t_cub3d *cub3d)
{
	//Compute how long we have until the reach the target frame time in milliseconds
	int timeToWait = cub3d->config->frame_time_length - (SDL_GetTicks() - ticksLastFrame);

	//Only delay execution if we are running too fast
	if (timeToWait > 0 && timeToWait <= cub3d->config->frame_time_length)
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
	main_loop(t_cub3d *cub3d)
{
	update(cub3d);
	render(cub3d);
	return (0);
}
void
	ft_run(t_cub3d cub3d)
{
	mlx_hook(cub3d.win, X_EVENT_KEY_PRESS, 0, &deal_key, &cub3d);
	mlx_hook(cub3d.win, X_EVENT_KEY_RELEASE, 0, &key_release, &cub3d);
	mlx_hook(cub3d.win, X_EVENT_KEY_EXIT, 0, &close_win,&cub3d);
	mlx_loop_hook(cub3d.mlx.mlx, &main_loop, &cub3d);
	mlx_loop(cub3d.mlx.mlx);
}

int
	main(int argc, char *argv[])
{
	t_cub3d		cub3d;
	t_config	config;
	int			save_option;

	save_option = 0;
	if (argc == 3)
		save_option = (!ft_strncmp(argv[2], "--save", 6));
	if (argc == 2 || (argc == 3 && save_option))
	{
		setup(&cub3d, &config, save_option, argv[1]);
		if (save_option)
			screenshot(&cub3d);
		ft_run(cub3d);
		return (EXIT_SUCCESS);
	}
	ft_exit_error(&cub3d, "ERROR: WRONG NUMBER OF ARGUMENTS.\n");
}
