#include "ft_ls.h"

char	*add_name(char *s, int isdir)
{
	char	*ret;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (s[len - 1] == '/')
		isdir = 0;
	ret = ft_strdup(s);
	if (ret == NULL)
		return (NULL);
	if (isdir == 1)
	{
		ret = ft_strjoin(ret, "/");
		if (ret == NULL)
			return (NULL);
	}
	return (ret);
}

int			check_for_self(char *s)
{
	if (s[0] == '.' && !s[1])
		return (0);
	if (s[0] == '.' && s[1] == '.' && !s[2])
		return (0);
	return (1);
}

void		print_objs(t_obj *obj, t_flags flags)
{
	while (obj)
	{
		if (obj->name[0] == '.' && flags.all_files == 0)
		{
			obj = obj->next;
			continue;
		}
		ft_printf("%s %s\n", obj->name, obj->full_name);
		obj = obj->next;
	}
	ft_printf("\n");
}

int			print_file(t_obj *list, t_flags flags)
{
	(void)flags;
	ft_printf("%s\n", list->name);
	return (1);
}

int			recursive_dir(t_obj *obj, t_flags flags)
{
	while (obj)
	{
		if (S_ISDIR(obj->buf.st_mode) && check_for_self(obj->name) == 1)
		{
			if (obj->name[0] == '.' && flags.all_files == 0)
			{
				obj = obj->next;
				continue ;
			}
			ft_printf("\n");
			print_dir(obj, flags);
		}
		obj = obj->next;
	}
	return (0);
}

int			error_dir(char *name)
{
	ft_printf("./ft_ls: %s dir cannot be open\n", name);
	return (1);
}

int			print_dir(t_obj *list, t_flags flags)
{
	DIR				*dir;
	struct dirent	*entry;
	t_obj			*obj;
	static int		pr_n = 0;
	char			*new_path;

	obj = NULL;
	if (!(dir = opendir(list->full_name)))
		return (error_dir(list->full_name));
	if (pr_n >= 1)
		print_file(list, flags);
	pr_n++;
	while ((entry = readdir(dir)) != NULL)
	{
		new_path = ft_strjoin(add_name(list->full_name, 1), entry->d_name);
		if (!(add_obj(&obj, create_obj(entry->d_name, new_path))))
			return (1);
	}
	print_objs(obj, flags);
	if (flags.recursive == 1)
		recursive_dir(obj, flags);
	closedir(dir);
	return (0);
}

int			print(t_obj *list, t_flags flags)
{
	while (list)
	{
		if (S_ISDIR(list->buf.st_mode))
			print_dir(list, flags);
		else
			print_file(list, flags);
		list = list->next;
	}
	return (0);
}

int			main(int argc, char **argv)
{
	t_flags		flags;
	int			n;
	t_obj		*list;

	init_flags(&flags);
	n = get_flags(argc, argv, &flags);
	if (!(list = get_args(argc, argv, n)))
		return (1);
	print_flags(flags);
	print_args(list);
	//sort_obj(&list, flags);
	print(list, flags);
	return (0);
}
