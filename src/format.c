#include "ft_ls.h"

void		compare(t_obj *obj, t_flags flags, t_format *format)
{
	int len;
	char type;
	int size_dev;

	(void)flags;
	type = obj->type;
	if ((len = ft_numlen(obj->buf.st_nlink)) > format->links)
		format->links = len;
	if ((len = ft_strlen(obj->usr->pw_name)) > format->owner)
		format->owner = len;
	if ((len = ft_strlen(obj->grp->gr_name)) > format->group)
		format->group = len;
	if (type == 'c' || type == 'b')
	{
		size_dev = 0;
		if ((len = ft_numlen(obj->major)) > format->size_major)
			format->size_major = len;
		size_dev += format->size_major;
		if ((len = ft_numlen(obj->minor)) > format->size_minor)
			format->size_minor = len;
		size_dev += format->size_minor;
		size_dev += 2;
		if (size_dev > format->size)
			format->size = size_dev;
	}
	else if ((len = ft_numlen(obj->buf.st_size)) > format->size)
		format->size = len;
}

void		init_format(t_format *format)
{
	format->links = 0;
	format->owner = 0;
	format->group = 0;
	format->size = 0;
	format->size_minor = 0;
	format->size_major = 0;
}

void		set_obj(t_obj *obj)
{
	obj->type = define_type(obj);
	obj->usr = getpwuid(obj->buf.st_uid);
	if (errno)
		error(obj->name);
	obj->grp = getgrgid(obj->buf.st_gid);
	if (errno)
		error(obj->name);
	if (obj->type == 'c' || obj->type == 'b')
	{
       // 	obj->major = major(obj->buf.st_size);
		if (errno)
			error(obj->name);
	 //       obj->minor = minor(obj->buf.st_rdev);
		if (errno)
			error(obj->name);
	}
}

void		formatting(t_obj *obj, t_flags flags)
{
	t_format format;
	t_obj	*tmp;

	(void)flags;
	init_format(&format);
	tmp = obj;
	while (obj)
	{
		set_obj(obj);
		compare(obj, flags, &format);
		obj = obj->next;
	}
	print_list(tmp, format);
}
