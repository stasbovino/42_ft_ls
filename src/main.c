#include "ft_ls.h"

void		error(char *s)
{
	ft_printf("./ft_ls: %s: %s\n", s, strerror(errno));
}

int			malloc_error(int check)
{
	static int n = 0;

	if (check == 1)
	{
		if (n == 1)
			return (1);
		else
			return (0);
	}
	ft_pritnf("malloc error\n");
	n++;
	return (1);
}

static void *free_names(char *name, char *full_name, int error)
{
	if (error == 1)
		malloc_error(0);
	else if (error == 0)
		error(full_name);
	if (name)
		free(name);
	if (full_name)
		free(full_name);
	return (NULL);
}

t_obj		*create_obj(char *name, char *full_name)
{
	t_obj		*new;

	if (!name || !full_name)
		return (free_names(name, full_name, 1));
	if (!(new = (t_obj*)malloc(sizeof(t_obj))))
		return (free_names(name, full_name, 1));
	if (lstat(full_name, new->buf) == -1)
	{
		free(new);
		return (free_names(name, full_name, 0));
	}
	new->name = name;
	new->full_name = full_name;
	new->next = NULL;
	return (new);
}

int			*add_obj(t_obj **dst, t_obj *new)
{
	if (!new)
	{
		if (malloc_error(1) == 1)
	}
}

t_obj		*get_args(int argc, char **argv, int n)
{
	t_obj *list;

	if (n == argc)
	{
	}
	else if (n == argc - 1)
	{
	}
	else
	{
	}
}

int			main(int argc, char **argv)
{
	t_flags		flags;
	int			n;
	t_obj		*list;

	init_flags(&flags);
	n = get_flags(argc, argv, &flags);
	list = get_args(argc, argv, n);
}
