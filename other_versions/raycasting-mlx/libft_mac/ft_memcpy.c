/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 09:22:31 by asydykna          #+#    #+#             */
/*   Updated: 2021/02/07 17:19:15 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*a;
	char	*b;

	if (dst && src)
	{
		a = (char *)src;
		b = (char *)dst;
		while (n > 0)
		{
			*b = *a;
			b++;
			a++;
			n--;
		}
	}
	return (dst);
}
