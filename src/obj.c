/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 09:41:05 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/11/07 09:41:06 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	*free_cr_obj(t_obj *new, char *full_name)
{
	if (errno)
		print_error(full_name);
	if (new)
	{
		if (new->name)
			free(new->name);
		if (new->full_name)
			free(new->full_name);
		free(new);
	}
	return (NULL);
}

void		init_obj(t_obj *new)
{
	new->group = NULL;
	new->owner = NULL;
	new->next = NULL;
	new->full_name = NULL;
	new->name = NULL;
	new->link_name = NULL;
	new->full_link_name = NULL;
	new->link_case = 0;
}

t_obj		*create_obj(char *name, char *full_name)
{
	t_obj		*new;

	if (!name || !full_name)
		return (free_cr_obj(NULL, name));
	new = (t_obj*)malloc(sizeof(t_obj));
	init_obj(new);
	if (lstat(full_name, &new->buf) == -1)
		return (free_cr_obj(new, full_name));
	if (!(new->name = ft_strdup(name)))
		return (free_cr_obj(new, full_name));
	if (!(new->full_name = ft_strdup(full_name)))
		return (free_cr_obj(new, full_name));
	if (S_ISLNK(new->buf.st_mode))
		if (get_link_data(new))
			return (free_cr_obj(new, full_name));
	return (new);
}

void		*free_obj(t_obj *lst)
{
	t_obj *tmp;

	while (lst)
	{
		tmp = lst->next;
		if (lst->name)
			free(lst->name);
		if (lst->full_name)
			free(lst->full_name);
		if (lst->group)
			free(lst->group);
		if (lst->owner)
			free(lst->owner);
		free(lst);
		lst = tmp;
	}
	return (NULL);
}

void		*add_obj(t_obj **dst, t_obj *new, t_flags flags)
{
	if (!new && errno == ENOMEM)
		return (free_obj(*dst));
	if (!new)
		return (dst);
	if (flags.list_output == 1)
		new->link_case = 0;
	if (*dst)
		new->next = *dst;
	*dst = new;
	return (dst);
}
