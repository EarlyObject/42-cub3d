/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setups.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 21:58:51 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/05 16:12:52 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
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
}

void
	init_config_arrays(t_config *config)
{
	int	i;

	i = 0;
	while (i < TEXTURES)
		config->tex_path[i++] = NULL;
	i = 0;
	while (i < TEXTURES)
		config->wallTexture[i++] = NULL;
	config->color[TEX_NORTH] = 0xCFE2F3;
	config->color[TEX_SOUTH] = 0xFF9900;
	config->color[TEX_WEST] = 0xFF44FF;
	config->color[TEX_EAST] = 0x44FF44;
	config->color[TEX_SKY] = 0x33C6E3;
	config->color[TEX_FLOOR] = 0xA0764C;
	i = 0;
	while (i < C_LAST)
		config->set[i++] = 0;
	config->sprites = NULL;
}

void
	init_config(t_config *config)
{
	config->width = 1280;
	config->height = 800;
	config->map = NULL;
	config->rows = 0;
	config->columns = 0;
	config->num_sprites = 0;
	config->tile_width = 0;
	config->tile_height = 0;
	config->direction = 0;
	init_config_arrays(config);
}

void
	init_cub3d(t_cub3d *cub3d)
{
	t_image		image;

	cub3d->win = NULL;
	image = (t_image){.img_ptr = NULL, .addr = NULL};
	cub3d->image = image;
	cub3d->plr = (t_player){};
	cub3d->wall = (t_wall){};
	init_screen(cub3d);
	cub3d->config = NULL;
	cub3d->sprt_data = (t_sprite){.x = 0, .y = 0, .txtr = 0, .dist = 0,
		.trnsf_x = 0, .trnsf_y = 0, .dr_st_x = 0, .dr_st_y = 0, .dr_end_x = 0,
		.dr_end_y = 0, .spr_scr_x = 0, .vMoveScreen = 0, .spr_h = 0, .spr_w = 0,
		.tex_x = 0, .tex_y = 0, .txtr_buf = NULL, .color = 0};
}

void
	setup(t_cub3d *cub3d, t_config *config, char *conf_path)
{
	printf("Starting SETUP\n");
	init_cub3d(cub3d);
	init_config(config);
	cub3d->config = config;
	if (!parse_config(config, conf_path))
		ft_exit_error(cub3d, "ERROR: INVALID MAP PARAMETERS.");
	resume_init_config(config);
	set_window_size(cub3d->config);
	init_player(cub3d);
	init_wall(cub3d);
	initialize_window(cub3d);
	loadTextures(cub3d);
	find_sprites(config);
}
