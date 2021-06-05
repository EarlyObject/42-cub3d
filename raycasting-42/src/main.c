/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:44:02 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/04 10:28:32 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

int
	main_loop(t_cub3d *cub3d)
{
	clear_color_buffer(cub3d, WHITE);
	draw_floor_ceiling(cub3d, 0, cub3d->config->height / 2 + 1, TEX_SKY);
	draw_floor_ceiling(
		cub3d, cub3d->config->height / 2 + 1, cub3d->config->height, TEX_FLOOR);
	manage_walls(cub3d);
	draw_sprites(cub3d);
	renderMapGrid(cub3d);
	renderMapPlayer(cub3d);
	renderMapSprites(cub3d);
	mlx_put_image_to_window(
		cub3d->mlx.mlx, cub3d->win, cub3d->image.img_ptr, 0, 0);
	return (0);
}

void
	ft_run(t_cub3d cub3d)
{
	mlx_hook(cub3d.win, X_EVENT_KEY_PRESS, 0, &deal_key, &cub3d);
	mlx_hook(cub3d.win, X_EVENT_KEY_EXIT, 0, &close_win, &cub3d);
	mlx_loop_hook(cub3d.mlx.mlx, &main_loop, &cub3d);
	mlx_loop(cub3d.mlx.mlx);
}

int
	main(int argc, char *argv[])
{
	t_cub3d		cub3d;
	t_config	config;
	int			save_option;

	save_option = 0;
	if (argc == 3)
		save_option = (!ft_strncmp(argv[2], "--save", 6));
	if (argc == 2 || (argc == 3 && save_option))
	{
		setup(&cub3d, &config, argv[1]);
		if (save_option)
			screenshot(&cub3d);
		ft_run(cub3d);
		return (EXIT_SUCCESS);
	}
	else
		ft_exit_error(&cub3d, "ERROR: WRONG NUMBER OF ARGUMENTS.\n");
	return (EXIT_SUCCESS);
}
