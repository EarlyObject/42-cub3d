/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:44:02 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/27 20:25:02 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

int main_loop();

int
	deal_key(int key_code, t_cub3d *cub3d)
{
	if (key_code == KEY_ESC)
	{
		exit(0);
	}
	if (key_code == KEY_W || key_code == KEY_FORWARD)
	{
		if(cub3d->config->map[(int)(cub3d->plr.posX + cub3d->plr.dirX * cub3d->plr.moveSpeed) + (cub3d->config->columns * (int)(cub3d->plr.posY))] - 48 == false)
			cub3d->plr.posX += cub3d->plr.dirX * cub3d->plr.moveSpeed;
		if(cub3d->config->map[(int)(cub3d->plr.posX) + (cub3d->config->columns * (int)(cub3d->plr.posY + cub3d->plr.dirY * cub3d->plr.moveSpeed))] - 48  == false)
			cub3d->plr.posY += cub3d->plr.dirY * cub3d->plr.moveSpeed;
	}
	if (key_code == KEY_S || key_code == KEY_BACKWARD)
	{
		if(cub3d->config->map[(int)(cub3d->plr.posX - cub3d->plr.dirX * cub3d->plr.moveSpeed) + (cub3d->config->columns * (int)(cub3d->plr.posY))] - 48  == false)
				cub3d->plr.posX -= cub3d->plr.dirX * cub3d->plr.moveSpeed;
		if(cub3d->config->map[(int)(cub3d->plr.posX) + (cub3d->config->columns * (int)(cub3d->plr.posY - cub3d->plr.dirY * cub3d->plr.moveSpeed))] - 48 == false)
				cub3d->plr.posY -= cub3d->plr.dirY * cub3d->plr.moveSpeed;
	}
	if (key_code == KEY_RIGHT)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = cub3d->plr.dirX;
		cub3d->plr.dirX = cub3d->plr.dirX * cos(-cub3d->plr.rotSpeed) - cub3d->plr.dirY * sin(-cub3d->plr.rotSpeed);
		cub3d->plr.dirY = oldDirX * sin(-cub3d->plr.rotSpeed) + cub3d->plr.dirY * cos(-cub3d->plr.rotSpeed);
		double oldPlaneX = cub3d->screen.planeX;
		cub3d->screen.planeX = cub3d->screen.planeX * cos(-cub3d->plr.rotSpeed) - cub3d->screen.planeY * sin(-cub3d->plr.rotSpeed);
		cub3d->screen.planeY = oldPlaneX * sin(-cub3d->plr.rotSpeed) + cub3d->screen.planeY * cos(-cub3d->plr.rotSpeed);
	}
	if (key_code == KEY_LEFT)
	{
		double oldDirX = cub3d->plr.dirX;
		cub3d->plr.dirX = cub3d->plr.dirX * cos(cub3d->plr.rotSpeed) - cub3d->plr.dirY * sin(cub3d->plr.rotSpeed);
		cub3d->plr.dirY = oldDirX * sin(cub3d->plr.rotSpeed) + cub3d->plr.dirY * cos(cub3d->plr.rotSpeed);
		double oldPlaneX = cub3d->screen.planeX;
		cub3d->screen.planeX = cub3d->screen.planeX * cos(cub3d->plr.rotSpeed) - cub3d->screen.planeY * sin(cub3d->plr.rotSpeed);
		cub3d->screen.planeY = oldPlaneX * sin(cub3d->plr.rotSpeed) + cub3d->screen.planeY * cos(cub3d->plr.rotSpeed);
	}
	if (key_code == KEY_D)
	{
		if(cub3d->config->map[(int)((cub3d->plr.posX + cub3d->screen.planeX * cub3d->plr.moveSpeed) + (cub3d->config->columns * (int)cub3d->plr.posY))] - 48  == false)
			cub3d->plr.posX += cub3d->screen.planeX * cub3d->plr.moveSpeed;
		if(cub3d->config->map[(int)((cub3d->plr.posX) + (cub3d->config->columns * (int)(cub3d->plr.posY + cub3d->screen.planeY * cub3d->plr.moveSpeed)))] - 48  == false)
			cub3d->plr.posY += cub3d->screen.planeY * cub3d->plr.moveSpeed;
	}
	if (key_code == KEY_A)
	{
		if(cub3d->config->map[(int)(cub3d->plr.posX - cub3d->screen.planeX * cub3d->plr.moveSpeed) + (cub3d->config->columns * (int)cub3d->plr.posY)] - 48  == false)
			cub3d->plr.posX -= cub3d->screen.planeX * cub3d->plr.moveSpeed;
		if(cub3d->config->map[(int)(cub3d->plr.posX) + (cub3d->config->columns * (int)(cub3d->plr.posY - cub3d->screen.planeY * cub3d->plr.moveSpeed))] - 48  == false)
			cub3d->plr.posY -= cub3d->screen.planeY * cub3d->plr.moveSpeed;

	}
	return (0);
}

/*int
key_release(int key_code, t_cub3d *cub3d)
{
	if (key_code == KEY_W || key_code == KEY_FORWARD)
		//cub3d->plr.walkDrcn = 0;
	if (key_code == KEY_S || key_code == KEY_BACKWARD)
		//cub3d->plr.walkDrcn = 0;
	if (key_code == KEY_RIGHT)
		//cub3d->plr.turnDrcn = 0;
	if (key_code == KEY_LEFT)
		//cub3d->plr.turnDrcn = 0;
	if (key_code == KEY_D)
		//cub3d->plr.moveSide = 0;
	if (key_code == KEY_A)
		//cub3d->plr.moveSide = 0;
	return (0);
}*/

//sort the sprites based on distance




//sort the sprites based on distance
/*void sortSprites(int* order, double* dist, int amount)
{
	std::vector<std::pair<double, int>> sprites(amount);
	for(int i = 0; i < amount; i++) {
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	std::sort(sprites.begin(), sprites.end());
	// restore in reverse order to go from farthest to nearest
	for(int i = 0; i < amount; i++) {
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
}*/

int
main_loop(t_cub3d *cub3d)
{

//1D Zbuffer
	double ZBuffer[cub3d->config->width];
	clear_color_buffer(cub3d, WHITE);

	//CEILING CASTING
	draw_ceiling(cub3d);
	//FLOOR CASTING
	draw_floor(cub3d);

	for(int x = 0; x < cub3d->config->width; x++)
	{
		//calculate ray position and direction
		double cameraX; //x-coordinate in camera space
		double rayDirX;
		double rayDirY;
		cameraX = 2 * x / (double)(cub3d->config->width) -1; //x-coordinate in camera space
		rayDirX = cub3d->plr.dirX + cub3d->screen.planeX * cameraX;
		rayDirY = cub3d->plr.dirY + cub3d->screen.planeY * cameraX;

		//which box of the map we're in
		int mapX = (int)cub3d->plr.posX;
		int mapY = (int)cub3d->plr.posY;

		//length of ray from current position to next x or y - side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (cub3d->plr.posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - cub3d->plr.posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (cub3d->plr.posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - cub3d->plr.posY) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (cub3d->config->map[mapX + (cub3d->config->columns * mapY)] == '1')
					hit = 1;
		}

		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0)
			perpWallDist = (mapX - cub3d->plr.posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - cub3d->plr.posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int) (cub3d->config->height / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + cub3d->config->height / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + cub3d->config->height / 2;
		if (drawEnd >= cub3d->config->height)
			drawEnd = cub3d->config->height - 1;

		//texturing calculations
		//int texNum = cub3d->config->map[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!
		int texNum = cub3d->config->map[mapX + (cub3d->config->columns *mapY)] - '0' - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if(side == 0)
		{
			wallX = cub3d->plr.posY + perpWallDist * rayDirY;
			if (rayDirX > 0)
				texNum += 2;
			else
				texNum += 3;
		}

		else
		{
			wallX = cub3d->plr.posX + perpWallDist * rayDirX;
			if (rayDirY < 0)
				texNum += 0;
			else
				texNum += 1;

		}

		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)(TEXTURE_WIDTH));
		if(side == 0 && rayDirX > 0) texX = TEXTURE_WIDTH - texX - 1;
		if(side == 1 && rayDirY < 0) texX = TEXTURE_WIDTH - texX - 1;

		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * TEXTURE_HEIGHT / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - cub3d->config->height / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int) texPos & (TEXTURE_HEIGHT - 1);
			texPos += step;
			uint32_t *walTextrBuf;
			walTextrBuf = cub3d->config->wallTexture[texNum]->addr;
			uint32_t color = walTextrBuf[(TEXTURE_HEIGHT * texY + texX)];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (side == 1)
				color = (color >> 1) & 8355711;
			//buffer[y][x] = color;
			drawPixel(cub3d, x, y, color);
		}
		//SET THE ZBUFFER FOR THE SPRITE CASTING
		ZBuffer[x] = perpWallDist; //perpendicular distance is used
	}


	//Uint32 buffer[cub3d->config->height][cub3d->config->width]; // y-coordinate first because it works per scanline
	draw_sprites(cub3d, ZBuffer);
	mlx_put_image_to_window(
			cub3d->mlx.mlx, cub3d->win, cub3d->image.img_ptr, 0, 0);
	return (0);

}



int
close_win(void)
{
	exit(0);
}

void
ft_run(t_cub3d cub3d)
{
	mlx_hook(cub3d.win, X_EVENT_KEY_PRESS, 0, &deal_key, &cub3d);
	//mlx_hook(cub3d.win, X_EVENT_KEY_RELEASE, 0, &key_release, &cub3d);
	mlx_hook(cub3d.win, X_EVENT_KEY_EXIT, 0, &close_win, &cub3d);
	mlx_loop_hook(cub3d.mlx.mlx, &main_loop, &cub3d);
	mlx_loop(cub3d.mlx.mlx);
}

/*int
main_loop()
{

	return (0);
}*/



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
		setup(&cub3d, &config, argv[1]);
		if (save_option)
			screenshot(&cub3d);
		ft_run(cub3d);
		return (EXIT_SUCCESS);
	}
	else
		ft_exit_error(&cub3d, "ERROR: WRONG NUMBER OF ARGUMENTS.\n");
	return (EXIT_SUCCESS);
}
