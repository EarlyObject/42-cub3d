/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 09:10:17 by asydykna          #+#    #+#             */
/*   Updated: 2021/02/09 11:57:43 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int
	countrows(char *s, char c)
{
	int	rows;

	rows = 0;
	while (s && *s && *s == c)
		s++;
	if (s && *s && *s != c)
		rows++;
	while (s && *s && *s != c)
		s++;
	if (s && *s && *s == c)
		rows += countrows(s, c);
	return (rows);
}

static int
	count_chars(char *s, char c)
{
	int	chrs;

	chrs = 0;
	while (s && s[chrs] && s[chrs] != c)
		chrs++;
	return (chrs);
}

char
	**ft_split(char const *s, char c)
{
	char	**temp;
	int		rows;
	int		i;
	int		j;

	i = -1;
	rows = countrows((char *)s, c);
	temp = ft_calloc(rows + 1, sizeof(char *));
	while (++i < rows)
	{
		while (*s == c)
			s++;
		temp[i] = ft_calloc(count_chars((char *)s, c) + 1, sizeof(char));
		j = 0;
		while (*s && *s != c)
		{
			temp[i][j++] = *s;
			s++;
		}
		temp[i][j] = '\0';
	}
	temp[i] = 0;
	return (temp);
}
