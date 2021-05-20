/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 12:00:55 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/17 21:25:54 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

static int
	str_to_color(t_str *str)
{
	int	i;
	int	color;
	int	tmp;

	i = 0;
	color = 0;
	while (str)
	{
		tmp = ft_atoi(str->content);
		if (tmp < 0 || tmp > 255)
			return (-1);
		color = color | (tmp << (16 - (i++ *8)));
		str = str->next;
	}
	return (color);
}

static int
	config_key(char const *line)
{
	if (line[0] == 'R' && line[1] == ' ')
		return (C_R);
	else if (line[0] == 'N' && line[1] == 'O')
		return (C_NO);
	else if (line[0] == 'S' && line[1] == 'O')
		return (C_SO);
	else if (line[0] == 'W' && line[1] == 'E')
		return (C_WE);
	else if (line[0] == 'E' && line[1] == 'A')
		return (C_EA);
	else if (line[0] == 'S' && line[1] == ' ')
		return (C_S);
	else if (line[0] == 'F' && line[1] == ' ')
		return (C_F);
	else if (line[0] == 'C' && line[1] == ' ')
		return (C_C);
	return (C_MAP);
}

int
	parse_dimensions(t_config *config, char const *line)
{
	int		i;
	int		tmp;
	t_str	*str;
	t_str	*param;

	i = 0;
	while (line[++i])
		if (line[i] != ' ' && line[i] < '0' && line[i] > '9')
			return (0);
	str = ft_split_new(line, ' ');
	if (!str || str_length(str) != 3)
		return (str_clear(&str));
	param = str->next;
	tmp = ft_atoi(param->content);
	if (tmp <= 1)
		return (str_clear(&str));
	config->width = tmp;
	param = param->next;
	tmp = ft_atoi(param->content);
	if (tmp <= 1)
		return (str_clear(&str));
	config->height = tmp;
	return (str_clear(&str) | 1);
}

int
	parse_line(t_config *config, char const *line, t_str **map_buffer)
{
	static int	empty_in_map = 0;
	static int	content_after = 0;
	int			length;
	int			key;

	length = ft_strlen(line);
	if (length == 0 && config->set[C_MAP])
		empty_in_map = 1;
	if (empty_in_map && content_after)
		return (0);
	if (length == 0)
		return (1);
	key = config_key(line);
	if (key != C_MAP && (config->set[key] || config->set[C_MAP]))
		return (0);
	if (key == C_R)
		return (parse_dimensions(config, line));
	else if (key >= C_NO && key <= C_S)
		return (parse_texture(config, key, line));
	else if (key == C_F || key == C_C)
		return (parse_color(config, key, line));
	config->set[key] = 1;
	if (empty_in_map)
		content_after = 1;
	return (!!str_add_back(map_buffer, ft_strdup(line)));
}

int
	parse_color(t_config *config, int key, char const *line)
{
	int				i;
	unsigned int	color;
	t_str			*str[2];

	i = 1;
	while (line[i])
		if (!ft_in_set(config, line[i++], " ,0123456789"))
			return (0);
	str[0] = NULL;
	str[1] = NULL;
	str[0] = ft_split_new(line, ' ');
	if (!str || str_length(str[0]) != 2
		|| !(str[1] = ft_split_new(str[0]->next->content, ','))
		|| str_length(str[1]) != 3)
		return (str_clear(&str[0]) || str_clear(&str[1]));
	color = str_to_color(str[1]);
	if ((int)color < 0)
		return (str_clear(&str[0]) || str_clear(&str[1]));
	if (key == C_F)
		config->c[TEX_FLOOR] = color;
	else
		config->c[TEX_SKY] = color;
	return ((str_clear(&str[0]) || str_clear(&str[1])) | 1);
}
