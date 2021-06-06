/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:00:58 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/04 15:13:47 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	calc_sprite(t_cub3d *cub3d, int i)
{
	double	invDet;

	cub3d->sprt_data.x = cub3d->config->sprites[i].x - cub3d->plr.posX;
	cub3d->sprt_data.y = cub3d->config->sprites[i].y - cub3d->plr.posY;
	invDet = 1.0 / (cub3d->screen.planeX * cub3d->plr.dirY
			- cub3d->plr.dirX * cub3d->screen.planeY);
	cub3d->sprt_data.trnsf_x = invDet * (cub3d->plr.dirY * cub3d->sprt_data.x
			- cub3d->plr.dirX * cub3d->sprt_data.y);
	cub3d->sprt_data.trnsf_y = invDet * (-cub3d->screen.planeY
			* cub3d->sprt_data.x + cub3d->screen.planeX * cub3d->sprt_data.y);
	cub3d->sprt_data.spr_scr_x = (int)((cub3d->config->width / 2)
			* (1 + cub3d->sprt_data.trnsf_x / cub3d->sprt_data.trnsf_y));
	cub3d->sprt_data.vMoveScreen = (int)(V_MOVE / cub3d->sprt_data.trnsf_y);
	cub3d->sprt_data.spr_h = abs((int)(cub3d->config->height
				/ (cub3d->sprt_data.trnsf_y))) / V_DIV;
	cub3d->sprt_data.dr_st_y = -cub3d->sprt_data.spr_h / 2
		+ cub3d->config->height / 2 + cub3d->sprt_data.vMoveScreen;
	if (cub3d->sprt_data.dr_st_y < 0)
		cub3d->sprt_data.dr_st_y = 0;
	cub3d->sprt_data.dr_end_y = cub3d->sprt_data.spr_h / 2
		+ cub3d->config->height / 2 + cub3d->sprt_data.vMoveScreen;
	if (cub3d->sprt_data.dr_end_y >= cub3d->config->height)
		cub3d->sprt_data.dr_end_y = cub3d->config->height - 1;
}

void
	get_spr_txtr_color(t_cub3d *cub3d, int i, int y)
{
	int	d;

	d = (y - cub3d->sprt_data.vMoveScreen) * 256 - cub3d->config->height
		* 128 + cub3d->sprt_data.spr_h * 128;
	cub3d->sprt_data.tex_y = ((d * TEXTURE_HEIGHT)
			/ cub3d->sprt_data.spr_h) / 256;
	cub3d->sprt_data.txtr_buf = cub3d->config
		->wallTexture[cub3d->config->sprites[i].txtr]->addr;
	cub3d->sprt_data.color = cub3d->sprt_data.txtr_buf[(TEXTURE_WIDTH
			* cub3d->sprt_data.tex_y + cub3d->sprt_data.tex_x)];
}

void
	draw_single_sprite(t_cub3d *cub3d, int i)
{
	int	stripe;
	int	y;

	stripe = cub3d->sprt_data.dr_st_x;
	while (stripe < cub3d->sprt_data.dr_end_x)
	{
		cub3d->sprt_data.tex_x = (int)(256 * (stripe - (-cub3d->sprt_data
						.spr_w / 2 + cub3d->sprt_data.spr_scr_x))
				* TEXTURE_WIDTH / cub3d->sprt_data.spr_w) / 256;
		if (cub3d->sprt_data.trnsf_y > 0 && stripe > 0
			&& stripe < cub3d->config->width
			&& cub3d->sprt_data.trnsf_y < cub3d->wall.ZBuffer[stripe])
			y = cub3d->sprt_data.dr_st_y;
		while (y < cub3d->sprt_data.dr_end_y)
		{
			get_spr_txtr_color(cub3d, i, y);
			if ((cub3d->sprt_data.color
					 && cub3d->sprt_data.color != 0x00FF00FF))
				draw_pixel(cub3d, stripe, y, cub3d->sprt_data.color);
			y++;
		}
		stripe++;
	}
}

void
	draw_sprites(t_cub3d *cub3d)
{
	int	i;

	sort_sprites(cub3d, cub3d->config);
	i = cub3d->config->num_sprites - 1;
	while (i >= 0)
	{
		calc_sprite(cub3d, i);
		cub3d->sprt_data.spr_w = abs((int)(cub3d->config->height
					/ (cub3d->sprt_data.trnsf_y))) / U_DIV;
		cub3d->sprt_data.dr_st_x = -cub3d->sprt_data.spr_w
			/ 2 + cub3d->sprt_data.spr_scr_x;
		if (cub3d->sprt_data.dr_st_x < 0)
			cub3d->sprt_data.dr_st_x = 0;
		cub3d->sprt_data.dr_end_x = cub3d->sprt_data.spr_w / 2
			+ cub3d->sprt_data.spr_scr_x;
		if (cub3d->sprt_data.dr_end_x >= cub3d->config->width)
			cub3d->sprt_data.dr_end_x = cub3d->config->width - 1;
		draw_single_sprite(cub3d, i);
		i--;
	}
}

void
	find_sprites(t_config *config)
{
	int			i;
	int			j;
	int			x;
	int			s;

	s = 0;
	i = 0;
	while (i < config->rows)
	{
		j = 0;
		while (j < config->columns)
		{
			x = config->map[j + i * config->columns] - 48;
			if (x == 2)
			{
				config->sprites[s].x = j + 0.5;
				config->sprites[s].y = i + 0.5;
				config->sprites[s].txtr = 6;
				s++;
			}
			j++;
		}
		i++;
	}
}
