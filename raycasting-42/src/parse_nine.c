/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_nine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 12:00:55 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/13 18:41:26 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

static void
	set_dir_and_plane_no_so(t_cub3d *cub3d, int j)
{
	if (cub3d->config->map[j] == 'N')
	{
		cub3d->plr.dirX = 0;
		cub3d->plr.dirY = -1;
		cub3d->screen.planeX = 0.66;
		cub3d->screen.planeY = 0;
	}
	else if (cub3d->config->map[j] == 'S')
	{
		cub3d->plr.dirX = 0;
		cub3d->plr.dirY = 1;
		cub3d->screen.planeX = -0.66;
		cub3d->screen.planeY = 0;
	}
}

static void
	set_dir_and_plane_ea_we(t_cub3d *cub3d, int j)
{
	if (cub3d->config->map[j] == 'W')
	{
		cub3d->plr.dirX = -1;
		cub3d->plr.dirY = 0;
		cub3d->screen.planeX = 0;
		cub3d->screen.planeY = -0.66;
	}
	else if (cub3d->config->map[j] == 'E')
	{
		cub3d->plr.dirX = 1;
		cub3d->plr.dirY = 0;
		cub3d->screen.planeX = 0;
		cub3d->screen.planeY = 0.66;
	}
}

void
	set_player_vectors(t_cub3d *cub3d, int j, int i)
{
	cub3d->plr.posX = (double)i + 0.5;
	cub3d->plr.posY = (((double)j - i) / cub3d->config->max_len) + 0.5;
	if (cub3d->config->map[j] == 'N' || cub3d->config->map[j] == 'S')
		set_dir_and_plane_no_so(cub3d, j);
	else
		set_dir_and_plane_ea_we(cub3d, j);
	cub3d->checklist.player += 1;
	cub3d->config->map[j] = '0';
}

void
	check_mem_alloc(void *p)
{
	if (p == NULL)
	{
		write(2, "Error!\nMEMORY IS NOT ALLOCATED\n", 21);
		exit(2);
	}
}

bool
	is_all_digits(const char *s)
{
	int		i;

	i = 0;
	while (ft_isdigit(s[i]))
		i++;
	if (s[i] != '\0')
		return (0);
	else
		return (1);
}
