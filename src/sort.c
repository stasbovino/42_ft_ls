/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 10:11:03 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/11/07 11:22:14 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_obj	*obj_swap(t_obj *a, t_obj *b)
{
	a->next = b->next;
	b->next = a;
	return (b);
}

t_obj	*obj_reverse(t_obj *obj)
{
	t_obj *a;
	t_obj *b;
	t_obj *c;

	a = NULL;
	b = obj;
	c = (obj)->next;
	while (b)
	{
		c = (b)->next;
		(b)->next = a;
		a = b;
		b = c;
	}
	return (a);
}

t_obj	*obj_sort_time(t_obj *obj)
{
	if (!obj)
		return (NULL);
	if (obj->next && (obj->buf.st_mtime < obj->next->buf.st_mtime))
		obj = obj_swap(obj, obj->next);
	else if (obj->next && (obj->buf.st_mtime == obj->next->buf.st_mtime))
		if (obj->next && (obj->buf.st_mtimespec.tv_nsec
					< obj->next->buf.st_mtimespec.tv_nsec))
			obj = obj_swap(obj, obj->next);
	obj->next = obj_sort_time(obj->next);
	if (obj->next && (obj->buf.st_mtime < obj->next->buf.st_mtime))
	{
		obj = obj_swap(obj, obj->next);
		obj->next = obj_sort_time(obj->next);
	}
	else if (obj->next && (obj->buf.st_mtime == obj->next->buf.st_mtime))
		if (obj->next && (obj->buf.st_mtimespec.tv_nsec
					< obj->next->buf.st_mtimespec.tv_nsec))
		{
			obj = obj_swap(obj, obj->next);
			obj->next = obj_sort_time(obj->next);
		}
	return (obj);
}

t_obj	*obj_sort_ascii(t_obj *obj)
{
	if (!obj)
		return (NULL);
	if (obj->next && ft_strcmp(obj->name, obj->next->name) > 0)
		obj = obj_swap(obj, obj->next);
	obj->next = obj_sort_ascii(obj->next);
	if (obj->next && ft_strcmp(obj->name, obj->next->name) > 0)
	{
		obj = obj_swap(obj, obj->next);
		obj->next = obj_sort_ascii(obj->next);
	}
	return (obj);
}

int		sort_obj(t_obj **obj, t_flags flags)
{
	*obj = obj_sort_ascii(*obj);
	if (flags.modif_data_sort == 1)
		*obj = obj_sort_time(*obj);
	if (flags.reverse == 1)
		*obj = obj_reverse(*obj);
	return (1);
}
