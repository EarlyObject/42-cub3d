/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:01:17 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/04 18:25:47 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	load_textures(t_cub3d *cub3d)
{
	int		i;
	t_image	img;
	int		img_width;
	int		img_height;

	i = 0;
	while (i < TEXTURES)
	{
		if (cub3d->config->tex_path[i])
		{
			img.img_ptr = mlx_xpm_file_to_image(cub3d->mlx.mlx,
					cub3d->config->tex_path[i], &img_width, &img_height);
			if (img.img_ptr == NULL)
				ft_exit_error(cub3d, "ERROR: ERROR CONVERTING TEXTURE");
			img.addr = (uint32_t *)mlx_get_data_addr(img.img_ptr,
					 &img.bits_per_pixel, &img.line_length, &img.endian);
			if (img.addr != NULL )
				cub3d->config->wallTexture[i] = img.img_ptr;
			else
				ft_exit_error(cub3d, "ERROR: ERROR LOADING TEXTURE");
		}
		i++;
	}
}
