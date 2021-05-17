/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 20:29:12 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/17 21:27:21 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

static char
	*path_from_line(int start, char const *line)
{
	int		start_def;
	int		end;
	char	*path;

	start_def = start;
	if (!line)
		return (NULL);
	while (line[start] && line[start] == ' ')
		start++;
	end = ft_strlen(line);
	while (line[end] == ' ')
		end--;
	if (start == start_def || end - start <= 0
		|| !(path = ft_substr(line, start, end - start)))
		return (NULL);
	return (path);
}

static int
	texture_index(int key)
{
	if (key == C_NO)
		return (TEX_NORTH);
	else if (key == C_SO)
		return (TEX_SOUTH);
	else if (key == C_WE)
		return (TEX_WEST);
	else if (key == C_EA)
		return (TEX_EAST);
	return (TEX_SPRITE);
}

int
	parse_texture(t_config *config, int key, char const *line)
{
	char	*path;
	int		index;

	index = texture_index(key);
	if (config->tex_path[index])
	{
		free(config->tex_path[index]);
		config->tex_path[index] = NULL;
	}
	if (index == TEX_SPRITE)
		path = path_from_line(1, line);
	else
		path = path_from_line(2, line);
	if (!path)
		return (0);
	config->tex_path[index] = path;
	return (1);
}

t_str
	*ft_split_new(char const *org, char sep)
{
	int		i;
	int		start;
	t_str	*str;

	start = 0;
	i = 0;
	str = NULL;
	while (org[i])
	{
		if (org[i] == sep)
		{
			if (i - start > 0
				&& !str_add_back(&str, ft_substr(org, start, i - start)))
				return (PTR_CAST(str_clear(&str)));
			start = ++i;
		}
		else
			i++;
	}
	if (i - start > 0
		&& !str_add_back(&str, ft_substr(org, start, i - start)))
		return (PTR_CAST(str_clear(&str)));
	return (str);
}

int
	ft_endwith(char const *str, char const *end)
{
	int	length;
	int	end_length;

	length = ft_strlen(str);
	end_length = ft_strlen(end);
	if (end_length > length)
		return (0);
	return (!ft_strncmp(str + length - end_length, end, end_length));
}
