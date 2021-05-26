/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 08:27:58 by asydykna          #+#    #+#             */
/*   Updated: 2021/02/08 10:35:56 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list
	*ft_lstnew(void *content)
{
	t_list	*p;

	p = (t_list *)ft_calloc(sizeof (t_list), 1);
	if (!p)
		return (NULL);
	p->content = content;
	p->next = NULL;
	return (p);
}
