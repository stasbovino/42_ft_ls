#include "ft_ls.h"

void		error(char *s)
{
	if (!s) /* malloc error */
		ft_printf("./ft_ls: %s\n", strerror(errno));
	else
		ft_printf("./ft_ls: %s: %s\n", s, strerror(errno));
	errno = 0;
}
