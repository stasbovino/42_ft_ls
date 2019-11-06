#include "ft_ls.h"

void		print_objs(t_obj *obj, t_flags flags)
{
	int	new_line;

	if (!obj)
		return ;
	new_line = (obj) ? 1 : 0;
	if (flags.list_output == 1)
	{
		formatting(obj, flags);
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

int			print_argv(t_obj *list, t_flags flags)
{
	t_obj *tmp;
	t_obj *files;
	t_obj *dirs;

	files = NULL;
	dirs = NULL;
	while (list)
	{
		tmp = list->next;
		list->next = NULL;
		if (S_ISDIR(list->buf.st_mode))
			add_obj(&dirs, list);
		else
			add_obj(&files, list);
		list = tmp;
	}
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
		if (print_dir(dirs, flags, 1))
			if (errno == ENOMEM)
				return (1);
		dirs = dirs->next;
		if (dirs)
			ft_printf("\n");
	}
	if (tmp)
		free_obj(tmp);
	if (files)
		free_obj(files);
	return (0);
}

int			print(t_obj *list, t_flags flags, int count)
{
	if (count > 1)
		print_argv(list, flags);
	else
	{
		if (S_ISDIR(list->buf.st_mode))
		{
			if (print_dir(list, flags, 0))
				if (errno == ENOMEM)
					return (1);
		}
		else
			ft_printf("%s", list->name);
	}
	return (0);
}
