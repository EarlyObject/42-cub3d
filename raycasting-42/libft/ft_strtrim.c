/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 18:58:45 by asydykna          #+#    #+#             */
/*   Updated: 2021/02/08 11:53:03 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int
	ft_isin(const char *set, char needle)
{
	while (*set)
	{
		if (*set == needle)
			return (1);
		set++;
	}
	return (0);
}

char
	*ft_strtrim(char const *s1, char const *set)
{
	size_t	first;
	size_t	last;
	size_t	total;
	char	*p;

	if (!s1)
		return (NULL);
	first = 0;
	while (*(s1 + first) && ft_isin(set, *(s1 + first)))
		first++;
	last = ft_strlen(s1);
	while ((s1 + last - 1 > s1 + first) && ft_isin(set, *(s1 + last - 1)))
		last--;
	total = last - first;
	p = (char *)ft_calloc((total + 1), sizeof(char));
	return ((char *)ft_memmove(p, s1 + first, total));
}
