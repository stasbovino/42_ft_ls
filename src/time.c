#include "ft_ls.h"

void		display_time(struct stat buf)
{
	time_t	today;
	char	*s;

	time(&today);
	s = ctime(&(buf.st_mtime)) + 4;
	ft_printf(" %.12s ", s);
}
