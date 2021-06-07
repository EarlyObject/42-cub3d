/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 13:30:07 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/07 13:04:53 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

int
	clear_window(t_cub3d *cub3d)
{
	if (cub3d->image.img_ptr)
		mlx_destroy_image(cub3d->mlx.mlx, cub3d->image.img_ptr);
	if (cub3d->mlx.mlx && cub3d->win)
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
		if (cub3d->config->wallTexture[i] != NULL)
			mlx_destroy_image(cub3d->mlx.mlx, cub3d->config->wallTexture[i]);
		i++;
	}
}

int
	exit_game(t_cub3d *cub3d, int code)
{
	if (cub3d->config->sprites != NULL)
		free(cub3d->config->sprites);
	if (cub3d->wall.ZBuffer != NULL)
		free (cub3d->wall.ZBuffer);
	clear_textures(cub3d);
	clear_window(cub3d);
	exit(code);
}

void
	ft_exit_error(t_cub3d *cub3d, char const *message)
{
	if (message)
		printf("%s\n", message);
	exit_game(cub3d, EXIT_FAILURE);
}
