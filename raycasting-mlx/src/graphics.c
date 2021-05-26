/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:00:08 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/27 20:17:08 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

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
	mlx = mlx_init();
	if (!mlx)
		ft_exit_error(cub3d, "ERROR: MLX_INIT ERROR.");
	win = mlx_new_window(mlx, cub3d->config->width,
			cub3d->config->height, "cub3d");
	if (!win)
		ft_exit_error(cub3d, "ERROR: MLX_NEW_WINDOW ERROR.");
	cub3d->mlx.mlx = mlx;
	cub3d->win = win;
	cub3d->image.img_ptr = mlx_new_image(mlx, cub3d->config->width,
			cub3d->config->height);
	if (!cub3d->image.img_ptr)
		ft_exit_error(cub3d, "ERROR: MLX IMAGE ERROR.");
	cub3d->image.addr = (uint32_t *)mlx_get_data_addr(cub3d->image.img_ptr,
			&cub3d->image.bits_per_pixel, &cub3d->image.line_length,
			&cub3d->image.endian);
	return (1);
}

int
	clearColorBuffer(t_cub3d *cub3d, uint32_t color)
{
	int	i;

	i = 0;
	while (i < cub3d->config->width * cub3d->config->height)
	{
		cub3d->image.addr[i] = color;
		i++;
	}
	return (0);
}
