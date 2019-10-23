#include "ft_ls.h"

int			sizeof_obj(t_obj *obj)
{
	int n;

	n = 0;
	while (obj)
	{
		n++;
		obj = obj->next;
	}
	return (n);
}

int			recursive_dir(t_obj *obj, t_flags flags)
{
	char *new;

	while (obj)
		{
			if (S_ISDIR(obj->buf.st_mode) && check_for_self(obj->name_abs) == 1)
			{
				if (check_hidden(obj->name_abs) == 0 && flags.all_files == 0
						&& flags.all_files_without_self == 0)
				{
					obj = obj->next;
					continue ;
				}
				ft_printf("\n");
				if (!(new = add_name(obj->name, 1)))
					return (malloc_error());
				print_dir(new, flags, obj->buf);
			}
			obj = obj->next;
		}
	return (0);
}

int			main(int argc, char **argv)
{
	t_flags		flags;
	int			n;
	char		*name;
	struct stat	buf;

	init_flags(&flags);
	n = get_flags(argc, argv, &flags);
//	print_flags(flags);
	if (n - argc == 0)
	{
		name = create_name_start(".", 1);
		stat(name, &buf);
		print_dir(name, flags, buf); // .
		return (0);
	}
	if (n < argc - 1)
		flags.mult = 1;
	else
		flags.mult = 0;
	while (n < argc)
	{
		stat(argv[n], &buf);
		if (S_ISDIR(buf.st_mode))
			name = create_name_start(argv[n], 1);
		else
			name = create_name_start(argv[n], 0);
		print(name, flags, buf);
		n++;
	}
	return (0);
}
