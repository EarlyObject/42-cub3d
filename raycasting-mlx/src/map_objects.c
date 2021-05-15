/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 16:59:38 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/15 16:59:39 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	collocate_sprites(t_cub3d *cub3d)
{
	/*static sprite_t sprites[NUM_SPRITES] = {
	{ .x = 640, .y = 630, .texture =  8 }, // barrel
	{ .x = 660, .y = 690, .texture =  8 }, // barrel
	{ .x = 250, .y = 600, .texture = 10 }, // table
	{ .x = 250, .y = 600, .texture =  9 }, // light
	{ .x = 300, .y = 400, .texture = 11 }, // guard
	{ .x =  90, .y = 100, .texture = 12 } // armor
};
	cub3d->sprites = &sprites;*/

	for(int i = 0; i < NUM_SPRITES; i++)
	{
		sprite_t sprite;
		cub3d->sprites[i] = &sprite;
	}
	cub3d->sprites[0]->x = 640;
	cub3d->sprites[0]->y = 630;
	cub3d->sprites[0]->texture = 8; // barrel
	cub3d->sprites[0]->visible = true; // barrel

	cub3d->sprites[1]->x = 660;
	cub3d->sprites[1]->y = 690;
	cub3d->sprites[1]->texture = 8; // barrel
	cub3d->sprites[1]->visible = true; // barrel

	cub3d->sprites[2]->x = 250;
	cub3d->sprites[2]->y = 600;
	cub3d->sprites[2]->texture = 10; // table
	cub3d->sprites[2]->visible = true; // barrel

	cub3d->sprites[3]->x = 250;
	cub3d->sprites[3]->y = 600;
	cub3d->sprites[3]->texture = 9; // light
	cub3d->sprites[3]->visible = true; // barrel

	cub3d->sprites[4]->x = 300;
	cub3d->sprites[4]->y = 400;
	cub3d->sprites[4]->texture = 11; // guard
	cub3d->sprites[4]->visible = true; // barrel

	cub3d->sprites[5]->x = 90;
	cub3d->sprites[5]->y = 100;
	cub3d->sprites[5]->texture = 12;// armor
	cub3d->sprites[5]->visible = true; // barrel

}
