/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:01:17 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/17 21:16:52 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

static char *textureFileNames[NUM_TEXTURES] = {
	"./textures/redbrick.xpm", //[0]
	"./textures/purplestone.xpm",
	"./textures/mossystone.xpm",
	"./textures/graystone.xpm",
	"./textures/colorstone.xpm",
	"./textures/bluestone.xpm",
	"./textures/wood.xpm",
	"./textures/eagle.xpm",
	"./textures/barrel.xpm", //[8]
	"./textures/light.xpm", //[9]
	"./textures/table.xpm", //[10]
	"./textures/guard.xpm", //[11]
	"./textures/armor.xpm" //[12]
};

void
	loadTextures(t_cub3d *cub3d)
{
	int		i;
	t_image	img;
	int		img_width;
	int		img_height;

	i = 0;
	while (i < TEXTURES)
	{
		if (cub3d->config->tex_path[i])
			img.img_ptr = mlx_xpm_file_to_image(cub3d->mlx.mlx, cub3d->config->tex_path[i], &img_width, &img_height);
		if (img.img_ptr == NULL)
			ft_exit_error(cub3d, "ERROR: ERROR CONVERTING TEXTURE");
		img.addr = (uint32_t *)mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
		if (img.img_ptr != NULL)
		{
			cub3d->wallTexture[i] = img.img_ptr;
			printf("Loaded texture %d\n", i);
		}
		else
		{
			printf("ERROR LOADING TEXTURE %s\n", cub3d->config->tex_path[i]);
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
