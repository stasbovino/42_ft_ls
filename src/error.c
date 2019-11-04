#include "ft_ls.h"

void		error_stat(char *s)
{
	ft_printf("./ft_ls: %s: %s\n", s, strerror(errno));
}

int			malloc_error(int check)
{
	static int n = 0;

	if (check == 1)
	{
		if (n == 1)
			return (1);
		else
			return (0);
	}
	ft_printf("malloc error\n");
	n++;
	return (1);
}
