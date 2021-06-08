/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 15:01:58 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/13 19:22:14 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

static void
	swap_values(double *index, double *find)
{
	int	tmp;

	tmp = *index;
	*index = *find;
	*find = tmp;
}

void
	sort_sprites(double *order, double *distance, int num_spr, int index)
{
	int		pos;
	int		find;
	double	men_dis;

	*order *= *distance;
	index = 0;
	while (index < num_spr)
	{
		pos = index + 1;
		find = index;
		men_dis = distance[index];
		while (pos < num_spr)
		{
			if (distance[pos] > men_dis)
				find = pos;
			if (distance[pos] > men_dis)
				men_dis = distance[pos];
			pos++;
		}
		if (men_dis != distance[index])
			swap_values(&order[index], &order[find]);
		if (men_dis != distance[index])
			swap_values(&distance[index], &distance[find]);
		index++;
	}
}
