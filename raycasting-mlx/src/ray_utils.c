/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 22:23:05 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/25 22:24:03 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

bool
	isRayFacingDown(float angle)
{
	return (angle > 0 && angle < PI);
}

bool
	isRayFacingUp(float angle)
{
	return (!isRayFacingDown(angle));
}

bool
	isRayFacingRight(float angle)
{
	return (angle < 0.5 * PI || angle > 1.5 * PI);
}

bool
	isRayFacingLeft(float angle)
{
	return (!isRayFacingRight(angle));
}
