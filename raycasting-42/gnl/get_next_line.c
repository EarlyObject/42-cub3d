/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 08:40:14 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/05 16:10:40 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int
	get_return_code(char **line, int n, char **rdline, char *temp)
{
	if (n < 0)
		return (-1);
	if (n == 0)
		*line = ft_strdup((*rdline));
	else
		*line = ft_substr((*rdline), 0,
				(ft_strchr((*rdline), '\n') - (*rdline)));
	if (n > 0)
		temp = ft_strdup((*rdline) + (ft_strlen(*line) + +1));
	else
		temp = ft_strdup((*rdline) + (ft_strlen(*line) + +0));
	free_mem((void **) rdline);
	(*rdline) = temp;
	if (n == 0)
		free_mem((void **) rdline);
	if (n == 0)
		return (0);
	else
		return (1);
}

int	get_next_line(int fd, char **line)
{
	int			n;
	char		buf[BUFFER_SIZE + 1];
	static char	*rdline = NULL;
	char		*temp;

	n = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (rdline == NULL)
		rdline = make_str(0);
	else
		NULL;
	while (!ft_strchr(rdline, '\n'))
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n <= 0)
			break ;
		buf[n] = '\0';
		temp = ft_strjoin(rdline, buf);
		free_mem((void **)&rdline);
		rdline = temp;
	}
	return (get_return_code(line, n, &rdline, temp));
}

char
	*make_str(size_t size)
{
	char	*p;

	p = (char *)malloc(size + 1);
	if (!p)
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
