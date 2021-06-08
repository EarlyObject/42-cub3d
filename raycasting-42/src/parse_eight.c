/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_eight.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 12:00:55 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/13 18:13:04 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	ft_my_lstclear(t_d_list **lst, void (*del)(void *))
{
	t_d_list	*tmp;
	t_d_list	*start;

	if (!lst || !del)
		return ;
	start = *lst;
	while (start)
	{
		tmp = start->next;
		del(start->content);
		free(start);
		start = tmp;
	}
	*lst = NULL;
}

t_d_list
	*ft_my_lstnew(void *content, t_d_list **prev)
{
	t_d_list	*new;

	new = malloc(sizeof(t_d_list));
	if (!new)
		return (NULL);
	new->content = content;
	if (prev)
		new->previous = *prev;
	else
		new->previous = NULL;
	new->next = NULL;
	return (new);
}

bool
	is_map_valid(t_checklist *chk)
{
	if (!chk->no_txt || !chk->so_txt || !chk->ea_txt || !chk->we_txt || \
		!chk->sprite_txt || !chk->res_width || !chk->res_height || \
		!chk->floor_c || !chk->ceiling_c || !chk->m || !chk->player)
		return (0);
	if (chk->no_txt > 1 || chk->so_txt > 1 || chk->ea_txt > 1 || \
		chk->we_txt > 1 || chk->sprite_txt > 1 || chk->res_width > 1 || \
		chk->res_height > 1 || chk->floor_c > 1 || chk->ceiling_c > 1 || \
		chk->m > 1 || chk->player > 1)
		return (0);
	return (1);
}

void
	check_horizontal_border(const char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] == '1' || str[i] == ' '))
			ft_error_close(ERR_MAP_OPEN);
		i++;
	}
}

void
	check_vertical_borders(t_cub3d *cub3d)
{
	while (cub3d->tmp && cub3d->tmp->len != 0)
	{
		if (!(((char *)(cub3d->tmp->content))[0] == '1' || \
			((char *)(cub3d->tmp->content))[0] == ' ') || \
			!(((char *)(cub3d->tmp->content))[cub3d->tmp->len - 1] == '1' || \
			((char *)(cub3d->tmp->content))[cub3d->tmp->len - 1] == ' '))
			ft_error_close(ERR_MAP_OPEN);
		cub3d->tmp = cub3d->tmp->next;
	}
	cub3d->tmp = cub3d->lst;
}
