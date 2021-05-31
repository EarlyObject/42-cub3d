/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:24:16 by asydykna          #+#    #+#             */
/*   Updated: 2021/03/16 16:24:21 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	get_numlen(unsigned long long int num)
{
	int					len;
	unsigned long long	tmp;

	len = 0;
	tmp = num;
	if (num != 0)
	{
		while (tmp > 0)
		{
			len++;
			tmp /= 16;
		}
	}
	else
		len = 1;
	return (len);
}

char
	*add_hex_sign(char *p)
{
	char	*str;
	char	*tmp;

	tmp = p;
	if (ft_strncmp(p, "0", 1) == 0)
	{
		str = ft_make_str(3);
		ft_strlcpy(str, "0x0", 4);
	}
	else
		str = ft_strjoin("0x", p);
	free(tmp);
	return (str);
}

char
	*ft_itoa_hex(unsigned long long num, char format)
{
	char			*p;
	char			*base;
	int				len;
	unsigned int	rmd;

	len = get_numlen(num);
	p = ft_make_str(len);
	p[len--] = '\0';
	base = "0123456789abcdef";
	while (num >= 16 && len > 0)
	{
		rmd = num % 16;
		num = num / 16;
		if (format == 'X' && rmd > 9)
			*(p + len--) = base[rmd] - 32;
		else
			*(p + len--) = base[rmd];
	}
	if (format == 'X' && num > 9)
		*(p + len--) = base[num] - 32;
	else
		*(p + len--) = base[num];
	if (!format)
		p = add_hex_sign(p);
	return (p);
}
