/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:01:17 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/14 14:01:18 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

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
	int		i;
	t_image	img;
	int		img_width;
	int		img_height;

	i = 0;
	while (i < NUM_TEXTURES)
	{
		img.img_ptr = mlx_xpm_file_to_image(cub3d->mlx.mlx, textureFileNames[i], &img_width, &img_height);
		img.addr = (uint32_t *)mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
		if (img.img_ptr != NULL)
		{
			cub3d->wallTexture[i] = img.img_ptr;
			printf("Loaded texture %d\n", i);
		}
		else
		{
			printf("ERROR LOADING TEXTURE %s\n", textureFileNames[i]);
			ft_exit_error(cub3d, "ERROR: ERROR LOADING TEXTURE");
		}
		i++;
	}
}

//check the function, ptr or data?
void
	freeTextures(t_cub3d *cub3d) {
	int	i;

	i = 0;
	while (i < NUM_TEXTURES)
	{
		free(cub3d->wallTexture[i]);
		i++;
	}
}
