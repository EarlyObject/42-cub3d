/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:38:00 by asydykna          #+#    #+#             */
/*   Updated: 2021/02/01 23:48:21 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t
	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	total;
	size_t	original;

	original = dstsize;
	total = ft_strlen(dst) + ft_strlen(src);
	while (*dst != 0 && dstsize > 0)
	{
		dst++;
		dstsize--;
	}
	if (dstsize == 0)
		return (ft_strlen(src) + original);
	while (*src != 0 && dstsize > 1)
	{
		*dst++ = *src++;
		dstsize--;
	}
	*dst = '\0';
	return (total);
}
