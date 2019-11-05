#include "ft_ls.h"

void		print_objs(t_obj *obj, t_flags flags)
{
	if (flags.list_output == 1)
		formatting(obj, flags);
	else
		while (obj)
		{
			if (obj->name[0] == '.' && flags.all_files == 0)
			{
				obj = obj->next;
				continue;
			}
			ft_printf("%s ", obj->name);
			obj = obj->next;
		}
	ft_printf("\n");
}

int			print_file(t_obj *list, t_flags flags)
{
	(void)flags;
	ft_printf("%s\n", list->name);
	return (1);
}

int			print(t_obj *list, t_flags flags)
{
	while (list)
	{
		if (S_ISDIR(list->buf.st_mode))
		{
			if (print_dir(list, flags))
				return (1);
		}
		else
			print_file(list, flags);
		list = list->next;
	}
	return (0);
}
