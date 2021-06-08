/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_six.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 12:00:55 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/09 18:34:00 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

_Bool
	is_valid_map_bit(char c)
{
	return (c == '0' || c == '1' || c == '2' || c == ' ' || \
			c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

void
	ft_error_close(int error_code)
{
	if (error_code == ERR_ARGC_MIN)
		write(2, "Error!\nMISSING MAP\n", 22);
	else if (error_code == ERR_ARGC_MAX)
		write(2, "Error!\nTOO MANY ARGUMENTS\n", 27);
	else if (error_code == ERR_MAP_VALIDITY)
		write(2, "Error!\nINVALID MAP\n", 25);
	else if (error_code == ERR_MAP_C)
		write(2, "Error!\nWRONG MAP PARAMETERS. CHECK COLORS.\n", 42);
	else if (error_code == ERR_MAP_OPEN)
		write(2, "Error!\nMAP BORDERS ARE NOT CLOSED\n", 29);
	else if (error_code == ERR_MAP_BAD_ARG)
		write(2, "Error!\nBAD MAP ARGUMENT\n", 23);
	exit(EXIT_FAILURE);
}

void
	check_map_bits(t_cub3d *cub3d)
{
	int		i;

	i = 0;
	while (cub3d->tmp->next != NULL)
	{
		while (is_valid_map_bit(((char *)(cub3d->tmp->content))[i]))
			i++;
		if ((((char *)(cub3d->tmp->content))[i]) != '\0')
			ft_error_close(ERR_MAP_VALIDITY);
		i = 0;
		cub3d->tmp = cub3d->tmp->next;
	}
	while (is_valid_map_bit(((char *)(cub3d->tmp->content))[i]))
		i++;
	if ((((char *)(cub3d->tmp->content))[i]) != '\0')
		ft_error_close(ERR_MAP_VALIDITY);
}

void
	free_lst_content(void *content)
{
	free(content);
	content = NULL;
}

bool
	is_all_print(const char *s)
{
	int		i;

	i = 0;
	while (ft_isprint((int)s[i]))
		i++;
	if (s[i] != '\0')
		return (0);
	else
		return (1);
}
