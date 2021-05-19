/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 10:34:30 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/17 21:26:58 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

int
	parse_map(t_config *config, t_str *map_buffer)
{
	int		*map;

	map = NULL;
	config->columns = check_top_bottom_borders(map_buffer);
	config->rows = check_left_right_borders(map_buffer);
	if ((config->columns <= 2) || (config->rows <= 2)
		|| !check_valid(config, map_buffer))
		return (0);
	map = (int *)malloc(sizeof(*map) * (config->rows * config->columns));
	if (!map)
		return (0);
	if (copy_map(config, map_buffer, map) != 1)
		return (0);
	config->map = map;
	return (1);
}

int
	parse_config(t_config *config, char const *conf_path)
{
	int			c_fd;
	char		*line;
	int			r;
	t_str		*map_buffer;

	if (!ft_endwith(conf_path, ".cub"))
		return (0);
	c_fd = open(conf_path, O_RDONLY);
	if (c_fd < 0)
		return (0);
	map_buffer = NULL;
	r = 1;
	while (get_next_line(c_fd, &line))
	{
		r = (r && parse_line(config, line, &map_buffer));
		free(line);
	}
	if (r && ft_strlen(line) > 0)
		r = !!str_add_back(&map_buffer, ft_strdup(line));
	free(line);
	close(c_fd);
	if (!r || !parse_map(config, map_buffer))
		return (str_clear(&map_buffer));
	str_clear(&map_buffer);
	return (1);
}

int
	ft_in_set(t_config *config, char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
		{
			config->direction = c;
			return (c);
		}
		i++;
	}
	return (0);
}
