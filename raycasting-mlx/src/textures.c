#include "textures.h"
#include <stdio.h>
#include "structs.h"
#include "../mlx/mlx.h"

static char *textureFileNames[NUM_TEXTURES] = {
	"./images/redbrick.xpm", //[0]
	"./images/purplestone.xpm",
	"./images/mossystone.xpm",
	"./images/graystone.xpm",
	"./images/colorstone.xpm",
	"./images/bluestone.xpm",
	"./images/wood.xpm",
	"./images/eagle.xpm",
	"./images/barrel.xpm", //[8]
	"./images/light.xpm", //[9]
	"./images/table.xpm", //[10]
	"./images/guard.xpm", //[11]
	"./images/armor.xpm" //[12]
};

void
	loadTextures(t_cub3d *cub3d)
{
	for (int i = 0; i < NUM_TEXTURES; i++) {
		void	*img;
		int		img_width;
		int		img_height;

		img_width = WINDOW_WIDTH;
		img_height = WINDOW_HEIGHT;

		img = (upng_t *)mlx_xpm_file_to_image(cub3d->mlx.mlx, textureFileNames[i], &img_width, &img_height);
		if (img != NULL)
		{
			textures[i] = img;
			printf("Loaded texture %d\n", i);
		}
		else
		{
			printf("Error loading texture %s\n", textureFileNames[i]);
		}
	}
}

void
	freeTextures() {
	for (int i = 0; i < NUM_TEXTURES; i++) {
		upng_free(textures[i]);
	}
}