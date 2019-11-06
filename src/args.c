#include "ft_ls.h"

t_obj		*get_args(int argc, char **argv, int n)
{
	t_obj *list;

	list = NULL;
	if (n == argc)
	{
		if (!(add_obj(&list, create_obj(".", "./"))))
			return (NULL);
	}
	else
		while (n < argc)
		{
			if (argv[n][0] == '/')
			{
				if (!(add_obj(&list, create_obj(argv[n], argv[n]))))
					return (NULL);
			}
			else if (argv[n][0] == '.' && !argv[n][1])
			{
				if (!(add_obj(&list, create_obj(".", "."))))
					return (NULL);
			}
			else if (!(add_obj(&list, create_obj(argv[n], argv[n]))))
				return (NULL);
			n++;
		}
	return (list);
}
