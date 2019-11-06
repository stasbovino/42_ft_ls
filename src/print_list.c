#include "ft_ls.h"
#include <stdio.h>

void		display_time(struct stat buf)
{
	time_t	today;
	char	*s;
	time_t	six;

	six = (time_t)15638400;
	time(&today);
	if ((buf.st_mtime - today) >= six || (today - buf.st_mtime)  >= six)
	{
		s = ctime(&(buf.st_mtime)) + 4;
		ft_printf("%.7s ", s);
		s = ctime(&(buf.st_mtime)) + 20;
		ft_printf("%.4s ", s);
	}
	else
	{
		s = ctime(&(buf.st_mtime)) + 4;
		ft_printf("%.12s ", s);
	}
}

void		create_rights(char type, t_obj *obj, char s[12])
{
	s[0] = type;
	s[1] = (S_IRUSR & obj->buf.st_mode) ? 'r' : '-';
	s[2] = (S_IWUSR & obj->buf.st_mode) ? 'w' : '-';

	s[3] = (S_IXUSR & obj->buf.st_mode) ? 'x' : '-';
	if (S_ISUID & obj->buf.st_mode)
		s[3] = (s[3] == 'x') ? 's' : 'S';

	s[4] = (S_IRGRP & obj->buf.st_mode) ? 'r' : '-';
	s[5] = (S_IWGRP & obj->buf.st_mode) ? 'w' : '-';

	s[6] = (S_IXGRP & obj->buf.st_mode) ? 'x' : '-';
	if (S_ISGID & obj->buf.st_mode)
		s[6] = (s[6] == 'x') ? 's' : 'S';

	s[7] = (S_IROTH & obj->buf.st_mode) ? 'r' : '-';
	s[8] = (S_IWOTH & obj->buf.st_mode) ? 'w' : '-';

	s[9] = (S_IXOTH & obj->buf.st_mode) ? 'x' : '-';
	if (S_ISDIR(obj->buf.st_mode) && (S_ISVTX & obj->buf.st_mode))
		s[9] = (s[9] == 'x') ? 't' : 'T';

	s[10] = '\0';
}

char		define_type(t_obj *obj)
{
	if (S_ISREG(obj->buf.st_mode))
		return ('-');
	if (S_ISDIR(obj->buf.st_mode))
		return ('d');
	if (S_ISBLK(obj->buf.st_mode))
		return ('b');
	if (S_ISCHR(obj->buf.st_mode))
		return ('c');
	if (S_ISLNK(obj->buf.st_mode))
		return ('l');
	if (S_ISFIFO(obj->buf.st_mode))
		return ('p');
	if (S_ISSOCK(obj->buf.st_mode))
		return ('s');
	return (0);
}

int			print_link_content(t_obj *obj)
{
	char *content;
	size_t size;
	size_t ret;

	size = 256;
	content = ft_strnew(size);
	ret = readlink(obj->full_name, content, size);
	ft_printf(" -> %s", content);
	free(content);
	return (ret);
}

void		print_list(t_obj *obj, t_format format)
{
	char type;
	char s[12];

	if (!obj)
		return ;
	ft_printf("total %d\n", format.blocks);
	while (obj)
	{
		type = obj->type;
		create_rights(type, obj, s);
		ft_printf("%-11s ", s);
		ft_printf("%*d ", format.links, obj->buf.st_nlink);
		ft_printf("%-*s  ", format.owner, obj->owner);
		ft_printf("%-*s  ", format.group, obj->group);
		if (type == 'c' || type == 'b')
			ft_printf("%3d, %3d ", obj->major, obj->minor);
		else
			ft_printf("%*d ", format.size, obj->buf.st_size);
		display_time(obj->buf);
		ft_printf("%s", obj->name);
		if (type == 'l')
			print_link_content(obj);
		ft_printf("\n");
		obj = obj->next;
	}
// file mode & links & owner & group & size & time & path
// for dir: 512-byte blocks used by the bloks in the directory
}
