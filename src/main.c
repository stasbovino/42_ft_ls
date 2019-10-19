#include "ft_ls.h"

int			check_for_self(char *s)
{
	if (s[0] == '.' && !s[1])
		return (0);
	if (s[0] == '.' && s[1] == '.')
		return (0);
	return (1);
}

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

int			print_dir(char *name, t_flags flags)
{
	DIR				*dir;
	struct dirent	*entry;
	struct stat		buf;
	char			*curr;
	t_queue			*queue;
	int i;

	if (!(dir = opendir(name)))
	{
		ft_printf("./ft_ls: No such file or directory\n");
		return (1);
	}
	print_name(name);
	queue = NULL;
	i = -1;
	while ((entry = readdir(dir)) != NULL)
	{
		curr = ft_strjoin(name, entry->d_name);
		ft_printf("%s ", entry->d_name);
//		ft_printf("%d-%s curr is %s", ++i, entry->d_name, curr);
		stat(curr, &buf);
		if (flags.recursive == 1 && S_ISDIR(buf.st_mode))
			if (check_for_self(entry->d_name))
			{
//				ft_printf(" + added");
				add_to_queue(&queue, curr);
			}
	}
	ft_printf("\n");
	ft_printf("\n");
	while (queue)
	{
		char *new;
		new = add_name(queue->name, 1);
		print_dir(new, flags);
//		ft_printf("%s ", (char*)(queue->content));
//		print_dir((char*)(queue->content), flags);
		queue = queue->next;
	}
	closedir(dir);
	return (0);
}

int			main(int argc, char **argv)
{
	t_flags flags;
	int		n;
	char	*name;

	init_flags(&flags);
	n = get_flags(argc, argv, &flags);
	print_flags(flags);
	while (n < argc)
	{
		name = create_name_start(argv[n], 1);
		ft_printf("%s\n", name);
		print_dir(name, flags);
		n++;
	}
	return (0);
}
