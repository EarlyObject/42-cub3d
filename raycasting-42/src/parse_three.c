/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 10:34:30 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/13 21:17:28 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

static void
	res_utils_two(t_cub3d *cub3d, t_config *config)
{
	if (config->height > cub3d->get_res_h)
		config->height = cub3d->get_res_h;
	if (config->width > cub3d->get_res_w)
		config->width = cub3d->get_res_w;
	if (config->height < 1 || config->width < 1)
		ft_exit_error(cub3d, "Resolution is less than 1.");
}

static void
	res_utils(t_cub3d *cub3d, char *str, t_config *config)
{
	char	*replaced;
	char	**temp;

	replaced = ft_replace(str, " ", "");
	check_mem_alloc(replaced);
	temp = ft_split(replaced, ',');
	check_mem_alloc(temp);
	if (two_d_map_counter(&temp) != 2 || \
			!(is_all_digits(temp[0])) || !(is_all_digits(temp[1])))
		ft_exit_error(cub3d, "Map params are bad. Check R.");
	if (config->width || config->height)
		ft_exit_error(cub3d, "Resolution param passed twice.");
	if (ft_strlen(temp[0]) < 5)
		config->width = ft_atoi(temp[0]);
	else
		config->width = cub3d->get_res_w;
	if (ft_strlen(temp[1]) < 5)
		config->height = ft_atoi(temp[1]);
	else
		config->height = cub3d->get_res_h;
	res_utils_two(cub3d, config);
	free(replaced);
	free_twod_array(temp);
	replaced = NULL;
	temp = NULL;
}

static void
	check_rgb(char **rgb)
{
	int				i;

	i = 0;
	while (rgb[i])
	{
		if (ft_strlen(rgb[i]) < 1 || ft_strlen(rgb[i]) > 3)
			ft_error_close(ERR_MAP_C);
		i++;
	}
	if (i != 3)
		ft_error_close(ERR_MAP_C);
}

void
	parse_color(t_cub3d *cub3d, const char *str, t_config *config)
{
	int				i;
	char			**rgb;

	i = 2;
	if ((str[0] == 'C' && config->c_color_parse) \
		|| (str[0] == 'F' && config->f_color_parse) || \
		!(ft_isdigit(str[1])) || !(count_commas(str)))
		ft_error_close(ERR_MAP_C);
	while (ft_isdigit(str[i]) || str[i] == ',')
		i++;
	if (i > 13 || str[i] != '\0')
		ft_error_close(ERR_MAP_C);
	rgb = ft_split(str + 1, ',');
	check_mem_alloc(rgb);
	check_rgb(rgb);
	set_color(cub3d, str, config, rgb);
	free_twod_array(rgb);
	rgb = NULL;
}

void
	parse_resolution(t_cub3d *cub3d, char *str, t_config *config)
{
	int	i;

	i = 0;
	if (str[0] == 'R' && str[1] == ' ')
		str += 2;
	while (str[i] == ' ')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == ' ')
		str[i] = ',';
	else
		ft_exit_error(cub3d, "BAD MAP PARAMETERS. CHECK RESOLUTION (R)");
	mlx_get_screen_size(cub3d->mlx.mlx, &cub3d->get_res_w, &cub3d->get_res_h);
	res_utils(cub3d, str, config);
	cub3d->checklist.res_height += 1;
	cub3d->checklist.res_width += 1;
}
