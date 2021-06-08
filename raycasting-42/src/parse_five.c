/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_five.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 20:29:12 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/10 23:17:51 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

static void
	save_path(t_cub3d *cub3d, char **dst, const char *src)
{
	while (*src == ' ')
		src++;
	if (*dst)
		ft_exit_error(cub3d, "BAD MAP PARAMETERS. CHECK TEXTURE PATHS");
	*dst = ft_strdup(src);
	check_mem_alloc(*dst);
}

static _Bool
	texture_paths_filled(t_config *config)
{
	return (config->tex_path[0] && config->tex_path[1] && \
			config->tex_path[2] && config->tex_path[3] && config->tex_path[6]);
}

static void
	parse_textures(t_cub3d *cub3d, const char *str, t_config *config)
{
	if (ft_strnstr(str, "NO", 2))
	{
		save_path(cub3d, &config->tex_path[0], str + 2);
		cub3d->checklist.no_txt += 1;
	}
	else if (ft_strnstr(str, "SO", 2))
	{
		save_path(cub3d, &config->tex_path[1], str + 2);
		cub3d->checklist.so_txt += 1;
	}
	else if (ft_strnstr(str, "WE", 2))
	{
		save_path(cub3d, &config->tex_path[2], str + 2);
		cub3d->checklist.we_txt += 1;
	}
	else if (ft_strnstr(str, "EA", 2))
	{
		save_path(cub3d, &config->tex_path[3], str + 2);
		cub3d->checklist.ea_txt += 1;
	}
	else if (str[0] == 'S' && cub3d->checklist.sprite_txt++ == 0)
		save_path(cub3d, &config->tex_path[6], str + 2);
	else
		ft_exit_error(cub3d, "BAD MAP PARAMETERS. CHECK TEXTURE PARAMETERS");
}

void
	manage_textures(t_cub3d *cub3d, const char *str, t_config *config)
{
	if (texture_paths_filled(config) || !(is_all_print(str)))
		ft_exit_error(cub3d, "BAD MAP PARAMETERS. CHECK TEXTURE PARAMETERS");
	parse_textures(cub3d, str, config);
}

void
	check_sign(const char *str, const char *previous, \
							const char *next, t_cub3d *cub3d)
{
	int		j;

	j = 1;
	while (j < cub3d->tmp->len - 1)
	{
		if (str[j] == 'N' || str[j] == 'S' || str[j] == 'E' || str[j] == 'W')
		{
			if (!(cub3d->config->player_direction))
				cub3d->config->player_direction = str[j];
			else
				ft_error_close(ERR_MAP_VALIDITY);
		}
		if (str[j] != '1' && str[j] != ' ')
		{
			if (str[j - 1] == ' ' || (str[j + 1] == ' ' || \
				str[j + 1] == '\0') || previous[j] == ' ' || next[j] == ' ')
				ft_error_close(ERR_MAP_OPEN);
		}
		j++;
	}
}
