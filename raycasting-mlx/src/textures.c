#include "textures.h"
#include <stdio.h>

static char *textureFileNames[NUM_TEXTURES] = {
	"./images/redbrick.png", //[0]
	"./images/purplestone.png",
	"./images/mossystone.png",
	"./images/graystone.png",
	"./images/colorstone.png",
	"./images/bluestone.png",
	"./images/wood.png",
	"./images/eagle.png",
	"./images/barrel.png", //[8]
	"./images/light.png", //[9]
	"./images/table.png", //[10]
	"./images/guard.png", //[11]
	"./images/armor.png" //[12]
};

void
	loadTextures()
{
	for (int i = 0; i < NUM_TEXTURES; i++) {
		upng_t* upng = upng_new_from_file(textureFileNames[i]);
		if (upng != NULL)
		{
			upng_decode(upng);
			if (upng_get_error(upng) == UPNG_EOK)
				textures[i] = upng;
			else
				printf("Error decoding texture file %s\n", textureFileNames[i]);
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