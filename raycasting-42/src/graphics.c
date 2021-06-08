/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:00:08 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/13 18:10:36 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

int
	init_window(t_cub3d *cub3d)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	if (!mlx)
		ft_exit_error(cub3d, "MLX_INIT ERROR.");
	win = mlx_new_window(mlx, cub3d->config->width,
			cub3d->config->height, "cub3D");
	if (!win)
		ft_exit_error(cub3d, "MLX_NEW_WINDOW ERROR.");
	cub3d->mlx.mlx = mlx;
	cub3d->win = win;
	cub3d->image.img_ptr = mlx_new_image(mlx, cub3d->config->width,
			cub3d->config->height);
	if (!cub3d->image.img_ptr)
		ft_exit_error(cub3d, "MLX IMAGE ERROR.");
	cub3d->image.addr = (uint32_t *)mlx_get_data_addr(cub3d->image.img_ptr,
			&cub3d->image.bits_per_pixel, &cub3d->image.line_length,
			&cub3d->image.endian);
	return (1);
}

void
	draw_pixel(t_cub3d *cub3d, int x, int y, uint32_t color)
{
	if (x >= 0 && x < cub3d->config->width
		&& y >= 0 && y < cub3d->config->height)
		cub3d->image.addr[(cub3d->config->width * y) + x] = color;
}
