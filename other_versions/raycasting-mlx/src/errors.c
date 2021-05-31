/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 13:30:07 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/14 13:30:08 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

int
	exit_game(t_cub3d *cub3d, int code)
{
	clear_config(cub3d->config);
	clear_window(cub3d);
	clear_textures(cub3d);
	//clear_sprites(&game->sprites);
	//free_mmry(cub3d);
	exit(code);
}

void
	ft_exit_error(t_cub3d *cub3d, char const *message)
{
	if (message)
		printf("%s\n", message);
	exit_game(cub3d, EXIT_FAILURE);
}
