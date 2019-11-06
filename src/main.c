#include "ft_ls.h"

char		*add_name(char *s, int isdir)
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
		ret = ft_strrejoin(ret, "/");
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

int			main(int argc, char **argv)
{
	t_flags		flags;
	int			n;
	t_obj		*list;

	init_flags(&flags);
	n = get_flags(argc, argv, &flags);
	if (!(list = get_args(argc, argv, n)))
		return (1);
//	print_flags(flags);
//	print_args(list);
	if (print(list, flags))
		return (1);
	free_obj(list);
	return (0);
}
