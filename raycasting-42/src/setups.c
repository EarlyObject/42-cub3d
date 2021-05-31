/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setups.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 21:58:51 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/28 09:30:23 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

/*void
	set_window_size(t_config *config)
{
	if (config->width > 1920)
		config->width = 1920;
	if (config->height > 1080)
		config->height = 1080;
	if (config->width < 848)
		config->width = 848;
	if (config->height < 480)
		config->height = 480;
}*/

/*void
	update(t_cub3d *cub3d)
{
	static int	ticksLastFrame = 0;
	int			timeToWait;
	float		deltaTime;

	timeToWait = cub3d->config->frame_time_length
		 - (SDL_GetTicks() - ticksLastFrame);
	if (timeToWait > 0 && timeToWait <= cub3d->config->frame_time_length)
	{
		SDL_Delay(timeToWait);
	}
	deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
	ticksLastFrame = SDL_GetTicks();
	movePlayer(cub3d, deltaTime);
	castAllRays(cub3d);
}

void
	configurate_sprites(t_cub3d *cub3d)
{
	count_sprites(cub3d->config);
	cub3d->sprites = (t_sprite *)malloc(
			sizeof(t_sprite) * cub3d->config->num_sprites);
	if (cub3d->sprites == NULL)
		ft_exit_error(cub3d, "ERROR: ERROR CREATING SPRITES ARRAY.");
	find_sprites(cub3d, cub3d->config);
}*/

/*void
	setup(t_cub3d *cub3d, t_config *config, int save_option, char *conf_path)
{
	printf("Starting SETUP\n");
	init_cub3d(cub3d);
	init_config(config);
	cub3d->config = config;
	if (!parse_config(config, conf_path))
		ft_exit_error(cub3d, "ERROR: INVALID MAP PARAMETERS.");
	set_window_size(cub3d->config);
	init_player(cub3d);
	cub3d->rays = (t_ray *)malloc(sizeof(t_ray) * (config->width));
	if (!cub3d->rays)
		ft_exit_error(cub3d, "ERROR: ERROR CREATING RAYS ARRAY.");
	initializeWindow(cub3d);
	loadTextures(cub3d);
	configurate_sprites(cub3d);
	if (save_option)
		screenshot(cub3d);
}

void
	screenshot(t_cub3d *cub3d)
{
	update(cub3d);
	render(cub3d);
	bmp_builder(cub3d, "screenshot.bmp");
	printf("SCREENSHOT MADE SUCCESSFULLY.");
	exit_game(cub3d, EXIT_SUCCESS);
}*/
