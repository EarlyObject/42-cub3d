/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:44:02 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/27 20:25:02 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"
#include <SDL2/SDL.h>

int
	render(t_cub3d *cub3d)
{
	clearColorBuffer(cub3d, GREEN);
	renderWallProjection(cub3d);
	renderSpriteProjection(cub3d, cub3d->config);
	renderMapGrid(cub3d);
	renderMapRays(cub3d);
	renderMapPlayer(cub3d);
	renderMapSprites(cub3d);
	mlx_put_image_to_window(
		cub3d->mlx.mlx, cub3d->win, cub3d->image.img_ptr, 0, 0);
	return (0);
}

void
	releaseResources(t_cub3d *cub3d)
{
	freeTextures(cub3d);
}

int
	main_loop(t_cub3d *cub3d)
{
	update(cub3d);
	render(cub3d);
	return (0);
}

void
	ft_run(t_cub3d cub3d)
{
	mlx_hook(cub3d.win, X_EVENT_KEY_PRESS, 0, &deal_key, &cub3d);
	mlx_hook(cub3d.win, X_EVENT_KEY_RELEASE, 0, &key_release, &cub3d);
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
		setup(&cub3d, &config, save_option, argv[1]);
		if (save_option)
			screenshot(&cub3d);
		ft_run(cub3d);
		return (EXIT_SUCCESS);
	}
	else
	{
		ft_exit_error(&cub3d, "ERROR: WRONG NUMBER OF ARGUMENTS.\n");
	}
}
