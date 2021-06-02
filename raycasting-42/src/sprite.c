/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:00:58 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/28 09:16:55 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

float
	distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void
	swap_sprites(t_sprite *visibleSprites, t_sprite *temp, int i, int j)
{
	(*temp) = visibleSprites[i];
	visibleSprites[i] = visibleSprites[j];
	visibleSprites[j] = (*temp);
}

void
	sort_sprites(t_cub3d *cub3d)
{
	int 		i;
	int 		j;
	t_sprite	temp;

	i = 0;
	while (i < cub3d->config->num_sprites)
	{
		cub3d->config->sprites[i].distance = distanceBetweenPoints(
				cub3d->config->sprites[i].x, cub3d->config->sprites[i].y,
				cub3d->plr.posX, cub3d->plr.posY);
		i++;
	}
	i = 0;
	while (i < cub3d->config->num_sprites - 1)
	{
		j = 1;
		while (j < cub3d->config->num_sprites)
		{
			if (cub3d->config->sprites[i].distance < cub3d->config->sprites[j].distance)
			{
				swap_sprites(cub3d->config->sprites, &temp, i, j);
			}
			j++;
		}
		i++;
	}
}

void
	draw_sprites(t_cub3d *cub3d, const double *ZBuffer)
{
	sort_sprites(cub3d);


	//after sorting the sprites, do the projection and draw them
	for(int i = cub3d->config->num_sprites - 1; i >= 0 ; i--)
	{
		//translate sprite position to relative to camera
		double spriteX = cub3d->config->sprites[i].x - cub3d->plr.posX;
		double spriteY = cub3d->config->sprites[i].y - cub3d->plr.posY;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (cub3d->screen.planeX * cub3d->plr.dirY - cub3d->plr.dirX * cub3d->screen.planeY); //required for correct matrix multiplication

		double transformX = invDet * (cub3d->plr.dirY * spriteX - cub3d->plr.dirX * spriteY);
		double transformY = invDet * (-cub3d->screen.planeY * spriteX + cub3d->screen.planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

		int spriteScreenX = (int)((cub3d->config->width / 2) * (1 + transformX / transformY));

		//parameters for scaling and moving the sprites
#define uDiv 1
#define vDiv 1
#define vMove 0.0
		int vMoveScreen = (int)(vMove / transformY);

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(cub3d->config->height / (transformY))) / vDiv; //using "transformY" instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + cub3d->config->height / 2 + vMoveScreen;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + cub3d->config->height / 2 + vMoveScreen;
		if(drawEndY >= cub3d->config->height) drawEndY = cub3d->config->height - 1;

		//calculate width of the sprite
		int spriteWidth = abs( (int) (cub3d->config->height / (transformY))) / uDiv;
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= cub3d->config->width) drawEndX = cub3d->config->width - 1;

		//loop through every vertical stripe of the sprite on screen
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEXTURE_WIDTH / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if(transformY > 0 && stripe > 0 && stripe < cub3d->config->width && transformY < ZBuffer[stripe])
				for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					int d = (y-vMoveScreen) * 256 - cub3d->config->height * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * TEXTURE_HEIGHT) / spriteHeight) / 256;

					uint32_t *walTextrBuf;
					walTextrBuf = cub3d->config->wallTexture[cub3d->config->sprites[i].texture]->addr;
					Uint32 color = walTextrBuf[(TEXTURE_WIDTH * texY + texX)];

					//Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
					if((color && color != 0x00FF00FF))
						//	buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
						drawPixel(cub3d, stripe, y, color);
				}
		}
	}
}

int
	count_sprites(t_config *config)
{
	int			i;
	int			j;
	int			x;
	int			s;

	i = 0;
	s = 0;
	while (i < config->rows)
	{
		j = 0;
		while (j < config->columns)
		{
			x = config->map[j + i * config->columns] - 48;
			if (x == 2)
				s++;
			j++;
		}
		i++;
	}
	return (s);
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
				config->sprites[s].y = i +0.5;
				config->sprites[s].texture = 6;
				s++;
			}
			j++;
		}
		i++;
	}
}