/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:01:28 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/14 14:01:29 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	normalizeAngle(float *angle)
{
	*angle = remainder(*angle, TWO_PI);
	if (*angle < 0)
		*angle = TWO_PI + *angle;
}

float
	distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
