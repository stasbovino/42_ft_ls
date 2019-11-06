#include "ft_ls.h"

void		print_name(t_obj *list)
{
	ft_printf("%s:\n", list->name);
}

int			recursive_dir(t_obj *obj, t_flags flags)
{
	while (obj)
	{
//		usleep(1000);
		if (S_ISDIR(obj->buf.st_mode) && check_for_self(obj->name) == 1)
		{
			if (obj->name[0] == '.' && flags.all_files == 0)
			{
				obj = obj->next;
				continue ;
			}
			ft_printf("\n");
			if (print_dir(obj, flags))
				return (1);
		}
		obj = obj->next;
	}
	return (0);
}

int			print_dir(t_obj *list, t_flags flags)
{
	DIR				*dir;
	struct dirent	*entry;
	t_obj			*obj;
	static int		pr_n = 0;
	char			*new_path;

	obj = NULL;
	if (!(dir = opendir(list->full_name)))
	{
		error(NULL);
		return (1);
	}
	if (pr_n >= 1)
		print_name(list);
	pr_n++;
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] == '.' && flags.all_files == 0)
			continue ;
		if (!(new_path = ft_strrejoin(add_name(list->full_name, 1), entry->d_name)))
		{
			error(NULL);
			return (1);
		}
		if (!(add_obj(&obj, create_obj(entry->d_name, new_path))))
		{
			free(new_path);
			return (1);
		}
		free(new_path);
	}
	if (errno)
		error(NULL);
	sort_obj(&obj, flags);
	print_objs(obj, flags);
//	sleep(1);
	if (flags.recursive == 1)
		if (recursive_dir(obj, flags))
		{
			free_obj(obj);
			closedir(dir);
			return (1);
		}
	closedir(dir);
	free_obj(obj);
	return (0);
}
