#include "ft_ls.h"

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
			print_dir(obj, flags, 1);
		}
		obj = obj->next;
	}
	return (0);
}

int			print_dir(t_obj *list, t_flags flags, int printname)
{
	DIR				*dir;
	struct dirent	*entry;
	t_obj			*obj;
	char			*new_path;

	obj = NULL;
	if (!(dir = opendir(list->full_name)))
	{
		print_error(list->full_name);
		return (1);
	}
	if (printname)
		ft_printf("%s:\n", list->full_name);
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] == '.' && flags.all_files == 0)
			continue ;
		new_path = ft_strrejoin(add_name(list->full_name, 1), entry->d_name);
		add_obj(&obj, create_obj(entry->d_name, new_path));
		free(new_path);
	}
	if (errno)
		print_error(NULL);
	sort_obj(&obj, flags);
	print_objs(obj, flags);
//	sleep(1);
	if (flags.recursive == 1)
		recursive_dir(obj, flags);
	free_obj(obj);
	closedir(dir);
	return (0);
}
