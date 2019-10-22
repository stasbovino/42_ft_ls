#include "ft_ls.h"

t_obj		*create_obj(char *path, struct dirent data)
{
	t_obj		*new;
	char		*n;
	struct stat b;

	if (!(new = (t_obj*)malloc(sizeof(t_obj))))
	{
		malloc_error();
		return (NULL);
	}
	if (path == NULL)
	{
		if (!(n = ft_strdup(data.d_name)))
		{
			malloc_error();
			return (NULL);
		}
	}
	else if (!(n = ft_strjoin(path, data.d_name)))
	{
		free(new);
		malloc_error();
		return (NULL);
	}
	if ((stat(n, &b) == -1))
	{
		if (errno == EACCES)
			error(n);
		return (NULL);
	}
	new->next = NULL;
	new->name = ft_strdup(n);
	new->name_abs = ft_strdup(data.d_name);
	new->buf = b;
	return (new);
}

int			add_to_objs(t_obj **obj, t_obj *new)
{
	t_obj *tmp;

	if (!new)
		return (1);
	tmp = *obj;
	if (!tmp)
	{
		*obj = new;
		return (0);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}
