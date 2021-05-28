/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:00:08 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/28 09:06:10 by asydykna         ###   ########.fr       */
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

void
	draw_map_sprites(t_cub3d *cub3d, int i, int j)
{
	uint32_t	color;
	t_rectangle	rectangle;
	int			x;
	int			w;
	int			h;

	w = cub3d->config->width / cub3d->config->columns;
	h = cub3d->config->height / cub3d->config->rows;
	x = cub3d->config->map[j + i * cub3d->config->columns] - 48;
	color = 0xFF00FFFF;
	if (x == 2)
	{
		(rectangle) = (t_rectangle){.x = j * w * MINIMAP_SCALE_FACTOR,
			.y = i * h * MINIMAP_SCALE_FACTOR, .width = 2, .height = 2};
		drawRect(cub3d, rectangle, color);
	}
}

void
	renderMapSprites(t_cub3d *cub3d)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub3d->config->rows)
	{
		j = 0;
		while (j < cub3d->config->columns)
		{
			draw_map_sprites(cub3d, i, j);
			j++;
		}
		i++;
	}
}

void
	changeColorIntensity(uint32_t	*color, float factor)
{
	uint32_t	a;
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	a = (*color & 0xFF000000);
	r = (*color & 0x00FF0000) * factor;
	g = (*color & 0x0000FF00) * factor;
	b = (*color & 0x000000FF) * factor;
	*color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
}
