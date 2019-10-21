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

static int	error(char *s)
{
	ft_printf("./ft_ls: %s: %s\n", s, strerror(errno));
	return (1);
}
/*
int			print_dir(char *name, t_flags flags)
{
	DIR				*dir;
	struct dirent	*entry;
	struct stat		buf;
	char			*curr;
	t_queue			*queue;
	char			*new;

	if (!(dir = opendir(name)))
		return (error(name));
	print_name(name);
	queue = NULL;
	while ((entry = readdir(dir)) != NULL)
	{
		curr = ft_strjoin(name, entry->d_name);
		ft_printf("%s ", entry->d_name);
		stat(curr, &buf);
		if (flags.recursive == 1 && S_ISDIR(buf.st_mode))
			if (check_for_self(entry->d_name))
				add_to_queue(&queue, curr);
	}
	ft_printf("\n\n");
	while (queue)
	{
		new = add_name(queue->name, 1);
		print_dir(new, flags);
		queue = queue->next;
	}
	closedir(dir);
	return (0);
}

*/

int			print(char *s, t_flags flags, struct stat *buf)
{
	if (S_ISDIR(buf.st_mode))
		print_dir();
	else if (S_ISREG(buf.st_mode))
		print_file();
	else if (S_ISLNK(buf.st_mode))
		print_link();
	else if (S_ISCHR(buf.st_mode))
		print_char();
	else if (S_ISBLK(buf.st_mode))
		print_block();
	else if (S_ISFIFO(buf.st_mode))
		print_fifo();
	else if (S_ISSOCK(buf.st_mode))
		print_socket();
}

int			main(int argc, char **argv)
{
	t_flags		flags;
	int			n;
	char		*name;
	struct stat	buf;

	init_flags(&flags);
	n = get_flags(argc, argv, &flags);
	print_flags(flags);
	if (argc == 1)
	{
		print_dir(); // .
		return (0);
	}
	if (n < argc - 1)
		flags.mult = 1;
	else
		flags.mult = 0;
	while (n < argc)
	{
		stat(argv[n], &buf);
		print(argc[n], flags, &buf);
		n++;
	}
	return (0);
}
