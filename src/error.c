#include "ft_ls.h"

void		print_error(char *s)
{
	if (errno == ENOMEM)
	{
		ft_putstr_fd("./ft_ls: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		ft_putstr_fd("./ft_ls: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		errno = 0;
	}
}
