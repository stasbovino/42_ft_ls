/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 10:08:29 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/11/07 10:08:30 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			recursive_dir(t_obj *obj, t_flags flags)
{
	while (obj)
	{
		if (S_ISDIR(obj->buf.st_mode) && check_for_self(obj->name) == 1)
		{
			if (obj->name[0] == '.' && flags.all_files == 0)
			{
				obj = obj->next;
				continue ;
			}
			ft_printf("\n");
			print_dir(obj, flags, 1);
		}
		obj = obj->next;
	}
	return (0);
}

int			create_filling(t_obj **dst, t_flags flags, DIR *dir, t_obj *list)
{
	struct dirent	*entry;
	char			*new_path;

	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] == '.' && flags.all_files == 0)
			continue ;
		new_path = ft_strrejoin(add_name((list->link_case == 1)
					? list->full_link_name :
					list->full_name, 1), entry->d_name);
		add_obj(dst, create_obj(entry->d_name, new_path), flags);
		free(new_path);
	}
	return (0);
}

int			print_dir(t_obj *list, t_flags flags, int printname)
{
	DIR				*dir;
	t_obj			*obj;
	char			*to_open;

	obj = NULL;
	if (printname)
		ft_printf("%s:\n", list->full_name);
	to_open = (list->link_case == 1) ? list->full_link_name : list->full_name;
	if (!(dir = opendir(to_open)))
	{
		print_error((list->link_case == 1) ? list->link_name : list->name);
		return (1);
	}
	create_filling(&obj, flags, dir, list);
	if (errno)
		print_error(NULL);
	sort_obj(&obj, flags);
	print_objs(obj, flags);
	if (flags.recursive == 1)
		recursive_dir(obj, flags);
	free_obj(obj);
	closedir(dir);
	return (0);
}
