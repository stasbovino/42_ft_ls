/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 09:42:26 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/11/07 11:36:58 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_objs(t_obj *obj, t_flags flags)
{
	int	new_line;

	if (!obj)
		return ;
	new_line = (obj) ? 1 : 0;
	if (flags.list_output == 1)
	{
		formatting(obj, 1);
		return ;
	}
	else
		while (obj)
		{
			if (obj->name[0] == '.' && flags.all_files == 0)
			{
				obj = obj->next;
				continue;
			}
			ft_printf("%s", obj->name);
			if (obj->next)
				ft_printf(" ");
			obj = obj->next;
		}
	if (new_line)
		ft_printf("\n");
}

int			create_lists(t_obj **files, t_obj **dirs, t_obj *list, t_flags fl)
{
	t_obj *tmp;

	while (list)
	{
		tmp = list->next;
		list->next = NULL;
		(S_ISDIR(list->buf.st_mode)) ?
			add_obj(dirs, list, fl) : add_obj(files, list, fl);
		list = tmp;
	}
	return (0);
}

void		free_lists(t_obj *dirs, t_obj *files)
{
	if (dirs)
		free_obj(dirs);
	if (files)
		free_obj(files);
}

int			print_argv(t_obj *list, t_flags flags)
{
	t_obj *tmp;
	t_obj *files;
	t_obj *dirs;

	files = NULL;
	dirs = NULL;
	create_lists(&files, &dirs, list, flags);
	if (files)
	{
		sort_obj(&files, flags);
		print_objs(files, flags);
		ft_printf("\n");
	}
	tmp = dirs;
	if (dirs)
		sort_obj(&dirs, flags);
	while (dirs)
	{
		print_dir(dirs, flags, 1);
		dirs = dirs->next;
		if (dirs)
			ft_printf("\n");
	}
	free_lists(tmp, files);
	return (0);
}

int			print(t_obj *list, t_flags flags, int count)
{
	if (!list)
		return (1);
	if (count > 1)
		print_argv(list, flags);
	else
	{
		if (S_ISDIR(list->buf.st_mode) || list->link_case == 1)
			print_dir(list, flags, 0);
		else
		{
			if (flags.list_output == 1)
				formatting(list, 0);
			else
				ft_printf("%s\n", list->name);
		}
	}
	return (0);
}
