#include "ft_ls.h"

t_obj		*get_args(int argc, char **argv, int n)
{
	t_obj *list;
	char	*s;

	list = NULL;
	if (n == argc)
	{
		if (!(add_obj(&list, create_obj(".", "./."))))
			return (NULL);
	}
	else
		while (n < argc)
		{
			s = NULL;
			if (argv[n][0] == '/')
			{
				if (!(add_obj(&list, create_obj(argv[n], argv[n]))))
					return (NULL);
			}
			else if (!(add_obj(&list, create_obj(argv[n],
								s = ft_strjoin("./", argv[n])))))
				return (NULL);
			if (s)
				free(s);
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
