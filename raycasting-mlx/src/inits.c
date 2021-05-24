/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 08:34:45 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/21 08:34:46 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	init_player(t_cub3d *cub3d)
{
	cub3d->plr.x = cub3d->config->width / 2;
	cub3d->plr.y = cub3d->config->height / 2;
	cub3d->plr.width = 1;
	cub3d->plr.height = 1;
	cub3d->plr.turnDrcn = 0;
	cub3d->plr.walkDrcn = 0;
	cub3d->plr.rotAngle = -PI / 2;
	cub3d->plr.walkSpeed = 100;
	cub3d->plr.turnSpeed = 45 * (PI / 180);
	cub3d->plr.moveSide = 0;
}

void
	init_config(t_config *config)
{
	int	i;

	config->width = 848;
	config->height = 480;
	config->map = NULL;
	config->rows = 0;
	config->columns = 0;
	config->save_arg = 0;
	config->dist_proj_plane = ((config->width / 2) / tan(FOV_ANGLE / 2));
	config->direction = 0;
	i = 0;
	while (i < TEXTURES)
		config->tex_path[i++] = NULL;
	config->color[TEX_NORTH] = 0xFFFFFF;
	config->color[TEX_SOUTH] = 0xCCCCCC;
	config->color[TEX_WEST] = 0xFF44FF;
	config->color[TEX_EAST] = 0x44FF44;
	config->color[TEX_SKY] = 0x33C6E3;
	config->color[TEX_FLOOR] = 0xA0764C;
	i = 0;
	while (i < C_LAST)
		config->set[i++] = 0;
	i = 0;
	while (i < NUM_SPRITES)
		config->sprites[i++] = NULL;
}

void
	init_cub3d(t_cub3d *cub3d)
{
	int i;
	t_image image;
	t_player player;
	t_wall wall;
	t_rectangle rectangle;
	t_line line;
	cub3d->win = NULL;
	cub3d->image = image;
	cub3d->plr = player;
	//cub3d->mlx = NULL;
	cub3d->wall = wall;
	cub3d->rectangle = rectangle;
	cub3d->line = line;
	cub3d->config = NULL;
	cub3d->rays = NULL;
	i = 0;
	while (i < TEXTURES)
		cub3d->wallTexture[i++] = NULL;
	i = 0;
	while (i < NUM_SPRITES)
		cub3d->sprites[i++] = NULL;
}

void
	setup(t_cub3d *cub3d, t_config *config, int save_option, char *conf_path)
{
	printf("Starting SETUP\n");
	init_cub3d(cub3d);
	init_config(config);
	cub3d->config = config;
	//collocate_sprites(cub3d);
	if (!parse_config(config, conf_path))
	{
		printf("ERROR: INVALID MAP PARAMETERS.\n");
		exit(EXIT_FAILURE);
		//продумать выход с ошибкой
		//ft_exit_error(&cub3d, "ERROR: INVALID MAP PARAMETERS.\n");
	}
	if (cub3d->config->width > 1920)
		cub3d->config->width = 1920;
	if (cub3d->config->height > 1080)
		cub3d->config->height = 1080;
	if (cub3d->config->width < 848)
		cub3d->config->width = 848;
	if (cub3d->config->height < 480)
		cub3d->config->height = 480;
	init_player(cub3d);
	//могут быть ошибки!
	cub3d->rays = (t_ray *)malloc(sizeof(t_ray) * (config->width));
	if (!cub3d->rays)
		ft_exit_error(cub3d, "ERROR: ERROR CREATING RAYS ARRAY.");

	initializeWindow(cub3d);
	loadTextures(cub3d);
	find_sprites(cub3d, cub3d->config);
	if(save_option)
		screenshot(cub3d);
}