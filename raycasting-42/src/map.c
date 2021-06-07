/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:00:27 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/07 11:36:12 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

int
	getMapAt(t_config *config, int i, int j)
{
	int	x;
	int	addr;

	addr = j + i * config->columns;
	if (addr >= config->width * config->height)
		addr = config->width * config->height - 1;
	x = config->map[addr] - 48;
	if (x == 30 || x == 35 || x == 39 || x == 21)
		x = 0;
	return (x);
}
