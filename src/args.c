#include "ft_ls.h"

t_obj		*get_args(int argc, char **argv, int n)
{
	t_obj *list;

	list = NULL;
	if (n == argc)
	{
		if (!(add_obj(&list, create_obj(ft_strdup("."), ft_strdup("./.")))))
			return (NULL);
	}
	else
		while (n < argc)
		{
			if (!(add_obj(&list, create_obj(ft_strdup(argv[n]),
						ft_strjoin("./", argv[n])))))
				return (NULL);
			n++;
		}
	return (list);
}

void		print_args(t_obj *kek)
{
	while (kek)
	{
		ft_printf("%s && %s\n", kek->name, kek->full_name);
		kek = kek->next;
	}
}
