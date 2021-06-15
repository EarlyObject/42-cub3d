/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:00:58 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/13 19:21:46 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	calc_sprite_width(t_cub3d *cub3d)
{
	cub3d->spr_data.spr_w = abs((int)(cub3d->config->height
				/ (cub3d->spr_data.trnsf_y)));
	cub3d->spr_data.draw_start_x = -cub3d->spr_data.spr_w
		/ 2 + cub3d->spr_data.spr_scr_x;
	if (cub3d->spr_data.draw_start_x < 0)
		cub3d->spr_data.draw_start_x = 0;
	cub3d->spr_data.draw_end_x = cub3d->spr_data.spr_w / 2
		+ cub3d->spr_data.spr_scr_x;
	if (cub3d->spr_data.draw_end_x >= cub3d->config->width)
		cub3d->spr_data.draw_end_x = cub3d->config->width - 1;
}

void
	calc_sprite_height(t_cub3d *cub3d)
{
	cub3d->spr_data.spr_h = abs((int)(cub3d->config->height
				/ (cub3d->spr_data.trnsf_y)));
	cub3d->spr_data.draw_start_y = -cub3d->spr_data.spr_h / 2
		+ cub3d->config->height / 2;
	if (cub3d->spr_data.draw_start_y < 0)
		cub3d->spr_data.draw_start_y = 0;
	cub3d->spr_data.draw_end_y = cub3d->spr_data.spr_h
		/ 2 + cub3d->config->height / 2;
	if (cub3d->spr_data.draw_end_y >= cub3d->config->height)
		cub3d->spr_data.draw_end_y = cub3d->config->height - 1;
}

void
	calc_sprite(t_cub3d *cub3d, int i)
{
	double	invDet;

	cub3d->spr_data.sprite_x = cub3d->spr_data.buf[
		(int)cub3d->spr_data.order[i]][1] - cub3d->plr.posX;
	cub3d->spr_data.sprite_y = cub3d->spr_data.buf[
		(int)cub3d->spr_data.order[i]][0] - cub3d->plr.posY;
	invDet = 1.0 / (cub3d->screen.planeX * cub3d->plr.dirY
			- cub3d->plr.dirX * cub3d->screen.planeY);
	cub3d->spr_data.trnsf_x = invDet * (
			cub3d->plr.dirY * cub3d->spr_data.sprite_x - cub3d->plr.dirX
			* cub3d->spr_data.sprite_y);
	cub3d->spr_data.trnsf_y = invDet * (-cub3d->screen.planeY
			* cub3d->spr_data.sprite_x + cub3d->screen.planeX
			* cub3d->spr_data.sprite_y);
	cub3d->spr_data.spr_scr_x = (int)((cub3d->config->width / 2)
			* (1 + cub3d->spr_data.trnsf_x / cub3d->spr_data.trnsf_y));
	calc_sprite_height(cub3d);
	calc_sprite_width(cub3d);
}

void
	get_color_and_draw(t_cub3d *cub3d, int stripe, int y)
{
	int	d;

	d = (y) * 256 - cub3d->config->height * 128 + cub3d->spr_data.spr_h * 128;
	cub3d->spr_data.tex_y = ((d * TEXTURE_HEIGHT)
			/ cub3d->spr_data.spr_h) / 256;
	cub3d->spr_data.txtr_buf = (uint32_t *) cub3d->config->wallTexture[6]->addr;
	cub3d->spr_data.color = cub3d->spr_data.txtr_buf[(TEXTURE_WIDTH
			* cub3d->spr_data.tex_y + cub3d->spr_data.tex_x)];
	if ((cub3d->spr_data.color && cub3d->spr_data.color != 0x00FF00FF))
		draw_pixel(cub3d, stripe, y, cub3d->spr_data.color);
}

void
	draw_single_sprite(t_cub3d *cub3d)
{
	int		stripe;
	int		y;

	stripe = cub3d->spr_data.draw_start_x;
	while (stripe < cub3d->spr_data.draw_end_x)
	{
		cub3d->spr_data.tex_x = (int)(256 * (stripe - (
						-cub3d->spr_data.spr_w / 2 + cub3d->spr_data.spr_scr_x))
				* TEXTURE_WIDTH / cub3d->spr_data.spr_w) / 256;
		if (cub3d->spr_data.trnsf_y > 0 && stripe > 0
			&& stripe < cub3d->config->width
			&& cub3d->spr_data.trnsf_y < cub3d->wall.z_buffer[stripe])
		{
			y = cub3d->spr_data.draw_start_y;
			while (y < cub3d->spr_data.draw_end_y)
			{
				get_color_and_draw(cub3d, stripe, y);
				y++;
			}
		}
		stripe++;
	}
}
