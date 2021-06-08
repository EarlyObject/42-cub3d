/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:01:17 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/10 23:16:57 by asydykna         ###   ########.fr       */
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
			cub3d->config->wallTexture[i] = (t_image *)malloc(sizeof(t_image));
			cub3d->config->wallTexture[i]->img_ptr
				= mlx_xpm_file_to_image(cub3d->mlx.mlx,
					cub3d->config->tex_path[i], &img_width, &img_height);
			check_mem_alloc(cub3d->image.img_ptr);
			cub3d->config->wallTexture[i]->addr
				= (uint32_t *)mlx_get_data_addr(
					cub3d->config->wallTexture[i]->img_ptr,
					&img.bits_per_pixel, &img.line_length, &img.endian);
		}
		i++;
	}
}
