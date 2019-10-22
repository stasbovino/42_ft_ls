#include "ft_ls.h"

void		print_name(char *s)
{
	int i;
	int len;

	len = ft_strlen(s);
	if (len > 1 && s[0] == '.' && s[1] == '/')
		i = 1;
	else
		i = -1;
	while (s[i + 1] == '/')
		i++;
	while (++i < (len - 1))
		ft_printf("%c", s[i]);
	ft_printf(":\n");
}

int			sizeof_obj(t_obj *obj)
{
	int n;

	n = 0;
	while (obj)
	{
		n++;
		obj = obj->next;
	}
	return (n);
}

int			print_objs(t_obj *obj, t_flags flags)
{
	int tab;
	int newline;
	int ret;

	tab = 0;
	newline = (flags.all_files == 1 || sizeof_obj(obj) > 2) ? 1 : 0;
	ret = 0;
	while (obj)
	{
		if (tab == 1)
		{
			tab--;
			ft_printf(" ");
		}
		if ((((ret = check_for_self(obj->name_abs)) == 1)
					|| (ret == 0 && flags.all_files == 1)))
			if ((((ret = check_hidden(obj->name_abs)) == 1) ||
						(ret == 0 && (flags.all_files == 1
									  || flags.all_files_without_self == 1))))
			{
				print_file(obj->name_abs, flags, obj->buf);
				tab++;
			}
		obj = obj->next;
	}
	if (newline == 1)
		ft_printf("\n");
	return (0);
}

int			print_dir(char *path, t_flags flags, struct stat buf)
{
	DIR				*dir;
	struct dirent	*entry;
	t_obj			*obj;
	t_obj			*tmp;
	char			*new;
	static int		pr_n = 0;

	(void)buf;
	obj = NULL;
	if (!(dir = opendir(path)))
		return (error(path));
	if (pr_n >= 1)
	{
		print_name(path);
	}
	pr_n++;
	while ((entry = readdir(dir)) != NULL)
	{
		if ((add_to_objs(&obj, create_obj(path, *entry))))
			return (1);
	}
	print_objs(obj, flags);
	tmp = obj;
	if (flags.recursive == 1)
		while (tmp)
		{
			if (S_ISDIR(tmp->buf.st_mode) && check_for_self(tmp->name_abs) == 1)
			{
				if (check_hidden(tmp->name_abs) == 0
							&& flags.all_files == 0 && flags.all_files_without_self == 0)
				{
					tmp = tmp->next;
					continue ;
				}
				ft_printf("\n");
				if (!(new = add_name(tmp->name, 1)))
					return (malloc_error());
				print_dir(new, flags, tmp->buf);
			}
			tmp = tmp->next;
		}
	closedir(dir);
	return (0);
}

int			print_file(char *name, t_flags flags, struct stat buf)
{
	(void)flags;
	(void)buf;
	ft_printf("%s", name);
	return (0);
}

int			print(char *s, t_flags flags, struct stat buf)
{
	int ret;

	ret = 0;
	if (S_ISDIR(buf.st_mode))
		ret = print_dir(s, flags, buf);
	else if (S_ISREG(buf.st_mode))
		ret = print_file(s, flags, buf); 
/*	else if (S_ISLNK(buf.st_mode))
		print_link();
	else if (S_ISCHR(buf.st_mode))
		print_char();
	else if (S_ISBLK(buf.st_mode))
		print_block();
	else if (S_ISFIFO(buf.st_mode))
		print_fifo();
	else if (S_ISSOCK(buf.st_mode))
		print_socket();*/
	return (ret);
}

int			main(int argc, char **argv)
{
	t_flags		flags;
	int			n;
	char		*name;
	struct stat	buf;

	init_flags(&flags);
	n = get_flags(argc, argv, &flags);
//	print_flags(flags);
	if (n - argc == 0)
	{
		name = create_name_start(".", 1);
		stat(name, &buf);
		print_dir(name, flags, buf); // .
		return (0);
	}
	if (n < argc - 1)
		flags.mult = 1;
	else
		flags.mult = 0;
	while (n < argc)
	{
		stat(argv[n], &buf);
		if (S_ISDIR(buf.st_mode))
			name = create_name_start(argv[n], 1);
		else
			name = create_name_start(argv[n], 0);
		print(name, flags, buf);
		n++;
	}
	return (0);
}
