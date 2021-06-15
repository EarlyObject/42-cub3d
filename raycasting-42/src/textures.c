/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:01:17 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/15 14:54:46 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	load_textures(t_cub3d *cub3d, t_config *config)
{
	int		i;

	i = 0;
	while (i < TEXTURES)
	{
		if (config->tex_path[i])
		{
			config->wallTexture[i] = (t_image *)malloc(sizeof(t_image));
			config->wallTexture[i]->img_ptr
				= mlx_xpm_file_to_image(cub3d->mlx.mlx, config->tex_path[i],
					&config->wallTexture[i]->img_width,
					&config->wallTexture[i]->img_height);
			check_mem_alloc(cub3d->image.img_ptr);
			config->wallTexture[i]->addr
				= (uint32_t *)mlx_get_data_addr(
					config->wallTexture[i]->img_ptr,
					&config->wallTexture[i]->bits_per_pixel,
					&config->wallTexture[i]->line_length,
					&config->wallTexture[i]->endian);
		}
		i++;
	}
}
