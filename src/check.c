#include "ft_ls.h"

int			check_for_self(char *s)
{
	if (s[0] == '.' && !s[1])
		return (0);
	if (s[0] == '.' && s[1] == '.' && !s[2])
		return (0);
	return (1);
}

int			check_hidden(char *s)
{
	if (s[0] == '.')
		return (0);
	return (1);
}
