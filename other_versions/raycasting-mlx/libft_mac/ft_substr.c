/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 17:48:49 by asydykna          #+#    #+#             */
/*   Updated: 2021/02/08 11:58:36 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	slen;

	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	p = (char *)ft_calloc(len + 1, sizeof(char));
	if (len > ft_strlen(s))
		slen = ft_strlen(s);
	else
		slen = len;
	if (!p)
		return (NULL);
	ft_strlcpy(p, s + start, slen + 1);
	return (p);
}
