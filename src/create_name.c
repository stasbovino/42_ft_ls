#include "ft_ls.h"

char	*add_name(char *s, int isdir)
{
	char	*ret;
	int		len;
	int		curr;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	curr = 0;
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

char		*create_name_start(char *s, int isdir)
{
	char	*ret;
	int		len;
	int		curr;
	int		special_case;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	curr = 0;
	if (s[len - 1] == '/')
		isdir = 0;
	if (len > 1 && s[0] == '.' && s[1] == '/')
		curr = 0;
	else
		curr = 1;
	if (s[0] == '/')
		special_case = 1;
	else
		special_case = 0;
	if (curr == 1 && special_case == 0)
	{
		ret = ft_strjoin("./", s);
		if (ret == NULL)
			return (NULL);
	}
	else
	{
		ret = ft_strdup(s);
		if (ret == NULL)
			return (NULL);
	}
	if (isdir == 1)
	{
		ret = ft_strjoin(ret, "/");
		if (ret == NULL)
			return (NULL);
	}
	return (ret);
}
