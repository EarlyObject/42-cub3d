/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 20:23:44 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/10 23:09:16 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

int
	create_trgb(unsigned int t, unsigned int r, \
								unsigned int g, unsigned int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

bool
	count_commas(const char *str)
{
	int				commas;
	int				i;

	commas = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			commas++;
		i++;
	}
	return (commas == 2);
}

void
	fill_c_colors(t_cub3d *cub3d, t_config *config, char **rgb, int j)
{
	while (j++ < 2)
	{
		if (ft_strlen(rgb[j]) > 0 && ft_strlen(rgb[j]) < 4)
			config->ceiling_rgb[j] = ft_atoi(rgb[j]);
		else
			ft_exit_error(cub3d, "BAD CEILING COLOR VALUE (C)");
		if (config->ceiling_rgb[j] > 255 || config->ceiling_rgb[j] < 0)
			ft_exit_error(cub3d, "BAD CEILING COLOR VALUE (C)");
	}
	config->c_color_parse = 1;
	config->color[4] = create_trgb(0, config->ceiling_rgb[0], \
							config->ceiling_rgb[1], config->ceiling_rgb[2]);
	cub3d->checklist.ceiling_c += 1;
}

void
	set_color(t_cub3d *cub3d, const char *str, \
								t_config *config, char **rgb)
{
	int				j;

	j = -1;
	if (str[0] == 'C')
		fill_c_colors(cub3d, config, rgb, j);
	else if (str[0] == 'F')
	{
		while (j++ < 2)
		{
			if (ft_strlen(rgb[j]) > 0 && ft_strlen(rgb[j]) < 4)
				config->floor_rgb[j] = ft_atoi(rgb[j]);
			else
				ft_exit_error(cub3d, "BAD FLOOR COLOR VALUE (F)");
			if (config->floor_rgb[j] > 255 || config->floor_rgb[j] < 0)
				ft_exit_error(cub3d, "BAD FLOOR COLOR VALUE (F)");
		}
		config->f_color_parse = 1;
		config->color[5] = create_trgb(0, config->floor_rgb[0], \
							config->floor_rgb[1], config->floor_rgb[2]);
		cub3d->checklist.floor_c += 1;
	}
	else
		ft_error_close(ERR_MAP_C);
}

size_t
	find_max_len(t_cub3d *cub3d)
{
	int		max;

	max = 0;
	while (cub3d->tmp->next != NULL)
	{
		if (max < cub3d->tmp->len)
			max = cub3d->tmp->len;
		cub3d->tmp = cub3d->tmp->next;
	}
	cub3d->config->max_len = max;
	return (max);
}
