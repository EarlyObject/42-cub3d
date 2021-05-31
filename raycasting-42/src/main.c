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
#define mapWidth 24
#define mapHeight 24
//#define screenWidth 640
//#define screenHeight 480

int main_loop();

int worldMap[mapWidth][mapHeight]=
		{
				{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
				{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
				{4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
				{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
				{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
				{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
				{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
				{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
				{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
				{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
				{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
				{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
				{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
				{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
				{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
				{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
				{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
				{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
				{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
				{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
				{4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
				{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
				{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
				{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
		};

int
deal_key(int key_code, t_cub3d *cub3d)
{
	if (key_code == KEY_ESC)
	{
		exit(0);
	}
	if (key_code == KEY_W || key_code == KEY_FORWARD)
	{
		if(worldMap[(int)(cub3d->plr.posX + cub3d->plr.dirX * cub3d->plr.moveSpeed)][(int)(cub3d->plr.posY)] == false)
			cub3d->plr.posX += cub3d->plr.dirX * cub3d->plr.moveSpeed;
		if(worldMap[(int)(cub3d->plr.posX)][(int)(cub3d->plr.posY + cub3d->plr.dirY * cub3d->plr.moveSpeed)] == false)
			cub3d->plr.posY += cub3d->plr.dirY * cub3d->plr.moveSpeed;
	}
	if (key_code == KEY_S || key_code == KEY_BACKWARD)
	{
		if(worldMap[(int)(cub3d->plr.posX - cub3d->plr.dirX * cub3d->plr.moveSpeed)][(int)(cub3d->plr.posY)] == false)
			cub3d->plr.posX -= cub3d->plr.dirX * cub3d->plr.moveSpeed;
		if(worldMap[(int)(cub3d->plr.posX)][(int)(cub3d->plr.posY - cub3d->plr.dirY * cub3d->plr.moveSpeed)] == false)
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
	/*if (key_code == KEY_D)
		cub3d->plr.moveSide = +1;
	if (key_code == KEY_A)
		cub3d->plr.moveSide = -1;*/
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
			if (worldMap[mapX][mapY] > 0)
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
		int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if(side == 0) wallX = cub3d->plr.posY + perpWallDist * rayDirY;
		else          wallX = cub3d->plr.posX + perpWallDist * rayDirX;
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

	//SPRITE CASTING
	//sort sprites from far to close
	t_sprite sprite[NUM_SPRITES] =
			{
					{20.5, 11.5, 9, 0}, //green light in front of playerstart
					//green lights in every room
					{18.5,4.5, 9, 0},
					{10.0,4.5, 9, 0},
					{10.0,12.5,9, 0},
					{3.5, 6.5, 9, 0},
					{3.5, 20.5,9, 0},
					{3.5, 14.5,9, 0},
					{14.5,20.5,9, 0},

					//row of pillars in front of wall: fisheye test
					{18.5, 10.5, 11, 0},
					{18.5, 11.5, 11, 0},
					{18.5, 12.5, 11, 0},

					//some barrels around the map
					{21.5, 1.5, 11, 0},
					{15.5, 1.5, 11, 0},
					{16.0, 1.8, 11, 0},
					{16.2, 1.2, 11, 0},
					{3.5,  2.5, 11, 0},
					{9.5, 15.5, 11, 0},
					{10.0, 15.1,11, 0},
					{10.5, 15.8,11, 0},
			};
	//Uint32 buffer[cub3d->config->height][cub3d->config->width]; // y-coordinate first because it works per scanline



	//arrays used to sort the sprites
//	int spriteOrder[cub3d->config->num_sprites];
//	double spriteDistance[cub3d->config->num_sprites];

	//function used to sort the sprites
	//void sortSprites(int* order, double* dist, int amount);
	for(int i = 0; i < cub3d->config->num_sprites; i++)
	{
		//spriteOrder[i] = i;
	//	spriteDistance[i] = ((cub3d->plr.posX - sprite[i].x) * (cub3d->plr.posX - sprite[i].x) + (cub3d->plr.posY - sprite[i].y) * (cub3d->plr.posY - sprite[i].y)); //sqrt not taken, unneeded
		sprite[i].distance = distanceBetweenPoints(
				cub3d->sprites[i].x, cub3d->sprites[i].y,
				cub3d->plr.posX, cub3d->plr.posY);

		//sortSprites(spriteOrder, spriteDistance, NUM_SPRITES);
	}

	int z;
	int j;
	t_sprite	temp;
	z = 0;
	while (z < NUM_SPRITES - 1)
	{
		j = 1;
		while (j < NUM_SPRITES)
		{
			if (sprite[z].distance < sprite[j].distance)
			{
				swap_sprites(sprite, &temp, z, j);
			}
			j++;
		}
		z++;
	}

	/*int i;
	int j;
	i = 0;
	t_sprite	temp;
	while (i < NUM_SPRITES - 1)
	{
		j = 1;
		while (j < NUM_SPRITES)
		{
			if (sprite[i].distance < sprite[j].distance)
				swap_sprites(sprite, &temp, i, j);
			j++;
		}
		i++;
	}*/
//	sortSprites(spriteOrder, spriteDistance, cub3d->config->num_sprites);

	//after sorting the sprites, do the projection and draw them
	for(int i = 0; i < cub3d->config->num_sprites; i++)
	{
		//translate sprite position to relative to camera
		double spriteX = sprite[i].x - cub3d->plr.posX;
		double spriteY = sprite[i].y - cub3d->plr.posY;

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
					walTextrBuf = cub3d->config->wallTexture[sprite[i].texture]->addr;
					Uint32 color = walTextrBuf[(TEXTURE_WIDTH * texY + texX)];

					//Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
					if((color && color != 0x00FF00FF))
					//	buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
						drawPixel(cub3d, stripe, y, color);
				}
		}
	}



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
	//t_config	config;
	//int			save_option;
	printf("%d\n", argc);
	printf("%s\n", argv[0]);
	init_cub3d(&cub3d);
	init_config(&config);
	cub3d.config = &config;
	//cub3d.config->width = screenWidth;
	//cub3d.config->height = cub3d->config->height;

	init_player(&cub3d);
	init_screen(&cub3d);


	/*save_option = 0;
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
	else
	{
		ft_exit_error(&cub3d, "ERROR: WRONG NUMBER OF ARGUMENTS.\n");
	}*/

	initialize_window(&cub3d);
	loadTextures(&cub3d);
	ft_run(cub3d);
	return (EXIT_SUCCESS);

	//screen(screenWidth, screenHeight, 0, "Raycaster");

}
