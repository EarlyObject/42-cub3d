/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:44:13 by asydykna          #+#    #+#             */
/*   Updated: 2021/02/05 14:18:16 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)src;
	b = (unsigned char *)dst;
	while (n > 0)
	{
		*b = *a;
		if (*a == (unsigned char)c)
			return ((void *)b + 1);
		b++;
		a++;
		n--;
	}
	return (NULL);
}
