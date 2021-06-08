/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_four.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 20:16:49 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/09 18:32:39 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	append_spaces(const char *src, t_cub3d *cub3d, size_t len)
{
	char		*dst;
	size_t		i;

	i = 0;
	dst = ft_calloc(1, len + 1);
	check_mem_alloc(dst);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
	{
		dst[i] = ' ';
		i++;
	}
	dst[i] = '\0';
	free(cub3d->tmp->content);
	cub3d->tmp->content = dst;
}

void
	append_to_max_len(t_cub3d *cub3d)
{
	cub3d->config->columns = find_max_len(cub3d);
	cub3d->tmp = cub3d->lst;
	while (cub3d->tmp->next != NULL)
	{
		if (cub3d->tmp->len < cub3d->config->columns)
			append_spaces(cub3d->tmp->content, cub3d, cub3d->config->columns);
		cub3d->tmp = cub3d->tmp->next;
	}
	if (cub3d->tmp->len < cub3d->config->columns)
		append_spaces(cub3d->tmp->content, cub3d, cub3d->config->columns);
}

void
	convert_spaces_to_ones(t_cub3d *cub3d)
{
	int			i;

	i = 0;
	while (cub3d->tmp != NULL)
	{
		while (((char *)(cub3d->tmp->content))[i])
		{
			if (((char *)(cub3d->tmp->content))[i] == ' ')
			{
				((char *)(cub3d->tmp->content))[i] = '1';
			}
			i++;
		}
		i = 0;
		cub3d->tmp = cub3d->tmp->next;
	}
}

void
	parse_map(t_cub3d *cub3d)
{
	cub3d->tmp = cub3d->lst;
	check_map_bits(cub3d);
	check_horizontal_border(cub3d->tmp->content);
	cub3d->config->rows += 1;
	cub3d->tmp = cub3d->lst;
	check_horizontal_border(cub3d->tmp->content);
	cub3d->config->rows += 1;
	check_vertical_borders(cub3d);
	append_to_max_len(cub3d);
	cub3d->tmp = cub3d->lst->next;
	while (cub3d->tmp->next->next != NULL)
	{
		cub3d->config->rows += 1;
		check_sign(cub3d->tmp->content, cub3d->tmp->previous->content, \
					cub3d->tmp->next->content, cub3d);
		cub3d->tmp = cub3d->tmp->next;
	}
	cub3d->config->rows += 1;
	cub3d->tmp = cub3d->lst;
	convert_spaces_to_ones(cub3d);
}

void
	check_line_content(char *str, t_cub3d *cub3d, \
									bool *is_map_started)
{
	if (!(*str) && !(*is_map_started))
		return ;
	else if (!(*str) && *is_map_started)
		ft_exit_error(cub3d, "Map is not valid.");
	if (*str == ' ')
	{
		while (*str == ' ')
			str++;
	}
	if (*str == 'R')
		parse_resolution(cub3d, str, cub3d->config);
	else if (*str == 'N' || *str == 'S' || *str == 'W' || *str == 'E')
		manage_textures(cub3d, str, cub3d->config);
	else if (*str == 'C' || *str == 'F')
		manage_color(cub3d, str, cub3d->config);
	else if (!(*is_map_started) && (*str == '1' || *str == ' '))
	{
		*is_map_started = 1;
		parse_map(cub3d);
		cub3d->checklist.m += 1;
	}
	else
		ft_exit_error(cub3d, "INVALID MAP");
}
