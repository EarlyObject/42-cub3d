/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.color                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 08:40:14 by asydykna          #+#    #+#             */
/*   Updated: 2021/02/26 12:34:24 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	int			n;
	char		buf[BUFFER_SIZE + (n = 1)];
	static char	*rdline = NULL;
	char		*temp;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	rdline == NULL ? rdline = make_str(0) : NULL;
	while (!ft_strchr(rdline, '\n') && (n = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[n] = '\0';
		temp = ft_strjoin(rdline, buf);
		free_mem((void **)&rdline);
		rdline = temp;
	}
	if (n < 0)
		return (-1);
	*line = (n == 0) ? ft_strdup(rdline)
	: ft_substr(rdline, 0, (ft_strchr(rdline, '\n') - rdline));
	temp = ft_strdup(rdline + (ft_strlen(*line) + ((n > 0) ? +1 : +0)));
	free_mem((void **)&rdline);
	rdline = temp;
	if (n == 0)
		free_mem((void **)&rdline);
	return (n == 0) ? 0 : 1;
}

char
	*make_str(size_t size)
{
	char *p;

	if (!(p = (char *)malloc(size + 1)))
		return (NULL);
	ft_memset(p, 0, size + 1);
	return (p);
}

void
	free_mem(void **p)
{
	if (*p)
	{
		ft_memset(*p, 0, ft_strlen(*p));
		free(*p);
		*p = NULL;
	}
}

char
	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (!s || (long int)len < 0)
		return (NULL);
	ptr = (char *)malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	while (start < ft_strlen(s) && i < len)
	{
		ptr[i] = s[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}
