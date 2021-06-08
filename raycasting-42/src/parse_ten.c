/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ten.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 12:00:55 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/13 18:41:37 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	*ft_free_and_clear(char *str)
{
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	while (len != 0)
	{
		str[len] = '\0';
		len--;
	}
	str[len] = '\0';
	free(str);
	str = NULL;
	return (NULL);
}

char	**free_twod_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_free_and_clear(array[i]);
		i++;
	}
	free(array);
	return (NULL);
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

void
	create_map(t_cub3d *cub3d, t_config *config, int i)
{
	int		j;

	j = 0;
	check_mem_alloc(cub3d->config->map = ft_calloc(
			1, config->rows * config->columns + 1));
	while (cub3d->lst)
	{
		i = 0;
		while (((char *)cub3d->lst->content)[i])
		{
			cub3d->config->map[j] = ((char *)cub3d->lst->content)[i];
			if (config->map[j] == 'N' || config->map[j] == 'S'
				|| config->map[j] == 'W' || config->map[j] == 'E')
				set_player_vectors(cub3d, j, i);
			if (cub3d->config->map[j] == '2')
				cub3d->config->num_sprites++;
			i++;
			j++;
		}
		cub3d->lst = cub3d->lst->next;
	}
	cub3d->config->map[j] = '\0';
	cub3d->config->sprites = malloc(sizeof(t_sprite)
			* cub3d->config->num_sprites);
	check_mem_alloc(cub3d->config->sprites);
}

size_t
	two_d_map_counter(char ***s)
{
	size_t	i;

	i = 0;
	while ((*s)[i])
	{
		i++;
	}
	return (i);
}
