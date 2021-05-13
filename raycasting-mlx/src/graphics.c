#include "defs.h"
#include "structs.h"

static	SDL_Texture *colorBufferTexture;

int
	initializeWindow(t_cub3d *cub3d)
{
	void	*mlx;
	void	*win;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error initializing SDL.\n");
		return (false);
	}

	if (!(mlx = mlx_init()))
	{
		printf("MLX_INIT ERROR!!!");
		exit(1);
	}
	if (!(win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d")))
	{
		printf("MLX_NEW_WINDOW ERROR!!!");
		exit(1);
	}
	cub3d->mlx.mlx = mlx;
	cub3d->win = win;
	cub3d->image.img_ptr = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT); //check for leak
	cub3d->image.addr = (uint32_t *)mlx_get_data_addr(cub3d->image.img_ptr, &cub3d->image.bits_per_pixel, &cub3d->image.line_length, &cub3d->image.endian);
	printf("OK\n");
	return (0);
}

void
	destroyWindow(void)
{
	free(colorBuffer);
	//SDL_DestroyTexture(colorBufferTexture);
	//SDL_DestroyRenderer(renderer);
	//SDL_DestroyWindow(window);
	//SDL_Quit();
}

int
	clearColorBuffer(t_cub3d *cub3d, uint32_t color)
{
	for (int i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; i++)
		cub3d->image.addr[i] = color;
	return (0);
}

void
	renderColorBuffer(void)
{
	/* SDL_UpdateTexture(
		colorBufferTexture, 
		NULL, colorBuffer, 
		(int)((uint32_t)WINDOW_WIDTH * sizeof(uint32_t))
	);
	SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
	SDL_RenderPresent(renderer); */
}

void
	drawPixel(t_cub3d *cub3d, int x, int y, uint32_t color)
{
	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
		cub3d->image.addr[(WINDOW_WIDTH * y) + x] = color;
}

void
	drawRect(t_cub3d *cub3d, int x, int y, int width, int height, uint32_t color)
{
	for (int i = x; i <= (x + width); i++)
		for (int j = y; j <= (y + height); j++)
			drawPixel(cub3d, i, j, color);
}

void
	drawLine(t_cub3d *cub3d, int x0, int y0, int x1, int y1, uint32_t color)
{
	int	deltaX = (x1 - x0);
	int	deltaY = (y1 - y0);

	int longestSideLength = (abs(deltaX) >= abs(deltaY) ? abs(deltaX) : abs(deltaY));

	float xIncrement = deltaX / (float)longestSideLength;
	float yIncrement = deltaY / (float)longestSideLength;

	float currentX = x0;
	float currentY = y0;

	for (int i = 0; i < longestSideLength; i++)
	{
		drawPixel(cub3d, round(currentX), round(currentY), color);
		currentX += xIncrement;
		currentY += yIncrement;
	}
}
