/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setups.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 21:58:51 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/15 14:53:39 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

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
	config->sprites = NULL;
}

void
	init_config(t_config *config)
{
	config->width = 0;
	config->height = 0;
	config->map = NULL;
	config->rows = 0;
	config->columns = 0;
	config->num_sprites = 0;
	config->player_direction = 0;
	config->c_color_parse = 0;
	config->f_color_parse = 0;
	init_config_arrays(config);
}

static void
	init_checklist(t_checklist *checklist)
{
	checklist->no_txt = 0;
	checklist->so_txt = 0;
	checklist->ea_txt = 0;
	checklist->we_txt = 0;
	checklist->res_width = 0;
	checklist->res_height = 0;
	checklist->floor_c = 0;
	checklist->ceiling_c = 0;
	checklist->m = 0;
	checklist->player = 0;
	checklist->sprite_txt = 0;
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
	cub3d->spr_data = (t_sprite){.x = 0, .y = 0, .trnsf_x = 0,
		.trnsf_y = 0, .draw_start_x = 0, .draw_start_y = 0,
		.draw_end_x = 0, .draw_end_y = 0, .spr_scr_x = 0,
		.spr_h = 0, .spr_w = 0, .tex_x = 0, .tex_y = 0,
		.txtr_buf = NULL, .color = 0};
	cub3d->head = NULL;
	cub3d->lst = NULL;
	cub3d->tmp = NULL;
	cub3d->filename = NULL;
	cub3d->get_res_h = 0;
	cub3d->get_res_w = 0;
	cub3d->image = (t_image){.img_ptr = NULL, .addr = NULL,
		.bits_per_pixel = 0, .line_length = 0, .endian = 0};
	init_checklist(&cub3d->checklist);
}

void
	setup(t_cub3d *cub3d, t_config *config, char *conf_path)
{
	printf("STARTING SETUP\n");
	init_cub3d(cub3d);
	init_config(config);
	cub3d->config = config;
	init_wall(cub3d);
	init_parts(cub3d, conf_path);
	resume_init_config(cub3d);
	init_keys(cub3d);
	init_window(cub3d);
	load_textures(cub3d, cub3d->config);
	find_sprites(cub3d, config);
}
