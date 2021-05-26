/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_mngt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 13:42:53 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/26 13:42:54 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

int
	clear_config(t_config *config)
{
	int	i;

	i = 0;
	while (i < TEXTURES)
	{
		if (config->tex_path[i])
			free(config->tex_path[i]);
		config->tex_path[i] = NULL;
		i++;
	}
	if (config->map)
		free(config->map);
	config->map = NULL;
	free(config->visibleSprites);
	return (0);
}

int
	clear_window(t_cub3d *cub3d)
{
	if (cub3d->image.img_ptr)
		mlx_destroy_image(cub3d->mlx.mlx, cub3d->image.img_ptr);
	if (cub3d->win && cub3d->image.addr)
		mlx_destroy_window(cub3d->mlx.mlx, cub3d->win);
	return (0);
}

void
	clear_textures(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < TEXTURES)
	{
		if (cub3d->config->tex_path[i])
			mlx_destroy_image(cub3d->mlx.mlx, cub3d->config->tex_path[i]);
		cub3d->config->tex_path[i] = NULL;
		i++;
	}
}

/*
void
	free_mmry(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < cub3d.config->num_sprites)
		free(cub3d->sprites[i]);

	ft_split_new
	ft_substr - вроде очищается автоматом

	paths? str[]?
		   map
		   rays
	mlx
	config->tex_path
	cub3d->sprites
	free(cub3d->sprites);
	free(cub3d->config->tex_path);
	//free_mlx
	free(cub3d->rays);
	free(cub3d->config->map);
}*/
