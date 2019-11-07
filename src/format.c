/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 09:39:16 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/11/07 09:39:17 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		compare(t_obj *obj, t_format *format)
{
	int		len;
	char	type;
	int		size_dev;

	type = obj->type;
	if ((len = ft_numlen(obj->buf.st_nlink)) > format->links)
		format->links = len;
	if ((len = ft_strlen(obj->owner)) > format->owner)
		format->owner = len;
	if ((len = ft_strlen(obj->group)) > format->group)
		format->group = len;
	if (type == 'c' || type == 'b')
	{
		size_dev = 8;
		if (size_dev > format->size)
			format->size = size_dev;
	}
	else if ((len = ft_numlen(obj->buf.st_size)) > format->size)
		format->size = len;
	format->blocks += obj->buf.st_blocks;
}

void		init_format(t_format *format)
{
	format->links = 0;
	format->owner = 0;
	format->group = 0;
	format->size = 0;
	format->blocks = 0;
}

void		set_obj(t_obj *obj)
{
	struct passwd	*ow;
	struct group	*gr;

	obj->type = define_type(obj);
	ow = getpwuid(obj->buf.st_uid);
	if (errno)
		print_error(obj->name);
	obj->owner = ft_strdup(ow->pw_name);
	gr = getgrgid(obj->buf.st_gid);
	if (errno)
		print_error(obj->name);
	obj->group = ft_strdup(gr->gr_name);
	if (obj->type == 'c' || obj->type == 'b')
	{
		obj->major = major(obj->buf.st_rdev);
		obj->minor = minor(obj->buf.st_rdev);
	}
}

void		formatting(t_obj *obj)
{
	t_format	format;
	t_obj		*tmp;

	init_format(&format);
	tmp = obj;
	while (obj)
	{
		set_obj(obj);
		compare(obj, &format);
		obj = obj->next;
	}
	print_list(tmp, format);
}
