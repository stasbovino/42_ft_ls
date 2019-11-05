#include "ft_ls.h"

static void *free_names(char *name, char *full_name)
{
	if (errno)
		error(name);
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
		return (free_names(name, full_name));
	if (!(new = (t_obj*)malloc(sizeof(t_obj))))
		return (free_names(name, full_name));
	if (lstat(full_name, &new->buf) == -1)
	{
		free(new);
		return (free_names(name, full_name));
	}
	if (!(new->name = ft_strdup(name)))
	{
		free(new);
		return (free_names(name, full_name));
	}
	if (!(new->full_name = ft_strdup(full_name)))
	{
		free(new);
		return (free_names(name, full_name));
	}
	new->next = NULL;
	return (new);
}

void		*free_obj(t_obj *lst)
{
	t_obj *tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->name);
		free(lst->full_name);
		free(lst);
		lst = tmp;
	}
	return (NULL);
}

void		*add_obj(t_obj **dst, t_obj *new)
{
	if (!new && errno == 12)
		return (free_obj(*dst));
	if (!new)
		return (dst);
	if (*dst)
		new->next = *dst;
	*dst = new;
	return (dst);
}
