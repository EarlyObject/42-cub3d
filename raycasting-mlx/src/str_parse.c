/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 20:16:49 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/17 21:26:39 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

t_str
	*str_last(t_str *str)
{
	if (!str)
		return (NULL);
	while (str->next)
		str = str->next;
	return (str);
}

t_str
	*str_add_back(t_str **str, char *content)
{
	t_str	*first;
	t_str	*new;

	if (!content)
		return (NULL);
	if (!(new = (t_str*)malloc(sizeof(*new))))
		return (0);
	new->content = content;
	new->next = NULL;
	if (!*str)
		*str = new;
	else
	{
		first = *str;
		while ((*str)->next)
			*str = (*str)->next;
		(*str)->next = new;
		*str = first;
	}
	return (new);
}

int
	str_length(t_str *str)
{
	int	i;

	i = 0;
	while (str)
	{
		str = str->next;
		i++;
	}
	return (i);
}

int
	str_clear(t_str **list)
{
	t_str	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->content);
		free(*list);
		(*list) = tmp;
	}
	return (0);
}
