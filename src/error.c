#include "ft_ls.h"

int			error(char *s)
{
	ft_printf("./ft_ls: %s: %s\n", s, strerror(errno));
	return (1);
}

int			malloc_error(void)
{
	ft_printf("./ft_ls: malloc error\n");
	return (1);
}
