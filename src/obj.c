#include "ft_ls.h"

static void *free_names(char *name, char *full_name, int error)
{
	if (error == 1)
		malloc_error(0);
	else if (error == 0)
		error_stat(name);
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
	if (lstat(full_name, &new->buf) == -1)
	{
		free(new);
		return (free_names(name, full_name, 0));
	}
	new->name = name;
	new->full_name = full_name;
	new->next = NULL;
	return (new);
}

void		*free_obj(t_obj *srt)
{
	t_obj *tmp;

	while (srt)
	{
		tmp = srt->next;
		free(srt);
		srt = tmp;
	}
	return (NULL);
}

void		*add_obj(t_obj **dst, t_obj *new)
{
	if (!new && malloc_error(1) == 1)
		return (free_obj(*dst));
	if (!new)
		return (dst);
	if (*dst)
		new->next = *dst;
	*dst = new;
	return (dst);
}
