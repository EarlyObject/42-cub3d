/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 12:00:55 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/13 19:05:32 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void
	check_map_params(t_cub3d *cub3d)
{
	_Bool		map_started_flag;

	map_started_flag = 0;
	cub3d->lst = cub3d->head;
	while (cub3d->lst->next != NULL && !map_started_flag)
	{
		check_line_content(cub3d->lst->content, cub3d, &map_started_flag);
		if (!map_started_flag)
			cub3d->lst = cub3d->lst->next;
	}
}

void
	read_map(const int fd, t_cub3d *cub3d)
{
	int				bytes;

	cub3d->lst = ft_my_lstnew(NULL, NULL);
	check_mem_alloc(cub3d->lst);
	cub3d->head = cub3d->lst;
	while (true)
	{
		bytes = get_next_line(fd, (char **)&cub3d->lst->content);
		if (bytes == 1)
		{
			check_mem_alloc(cub3d->lst->content);
			cub3d->lst->next = ft_my_lstnew(NULL, &cub3d->lst);
			check_mem_alloc(cub3d->lst->next);
			cub3d->lst->len = ft_strlen(cub3d->lst->content);
			cub3d->lst = cub3d->lst->next;
		}
		else
			break ;
	}
	cub3d->lst->len = ft_strlen(cub3d->lst->content);
	if (bytes == -1)
		ft_exit_error(cub3d, "ERROR READING MAP");
	close(fd);
}

void
	init_parts(t_cub3d *cub3d, char *conf_path)
{
	int	i;

	i = 0;
	read_map(open(conf_path, O_RDONLY), cub3d);
	check_map_params(cub3d);
	cub3d->filename = conf_path;
	cub3d->filename[ft_strlen(cub3d->filename) - 4] = '\0';
	if (cub3d->checklist.m == 1)
		create_map(cub3d, cub3d->config, i);
	if (!(is_map_valid(&cub3d->checklist)))
		ft_exit_error(cub3d, "MAP FILE HAS ERRORS");
	ft_my_lstclear(&cub3d->head, free_lst_content);
	cub3d->head = NULL;
}

void
	parse_args(t_cub3d *cub3d, int ac, char *filename, char *save)
{
	_Bool		s_flag;
	int			fd;

	s_flag = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_exit_error(cub3d, "MAP FILE IS BAD");
	close(fd);
	if (!ft_endwith(filename, ".cub"))
		ft_exit_error(cub3d, "MAP EXTENSION IS WRONG");
	if (ac == 2 && !save)
		s_flag = 1;
	else if (ac == 3 && save != NULL)
		s_flag = (ft_endwith(save, "--save"));
	if (!s_flag)
		ft_exit_error(cub3d, "SAVE ARGUMENT IS INCORRECT");
}

void
	manage_color(t_cub3d *cub3d, const char *str, t_config *config)
{
	char			*tmp;

	if (!(is_all_print(str)))
		ft_error_close(ERR_MAP_C);
	tmp = ft_replace(str, " ", "");
	check_mem_alloc(tmp);
	parse_color(cub3d, tmp, config);
	free(tmp);
	tmp = NULL;
}
