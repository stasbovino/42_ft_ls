/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 09:39:53 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/11/07 09:39:54 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (isdir == 1)
		ret = ft_strrejoin(ret, "/");
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
	list = get_args(argc, argv, n, flags);
	print(list, flags, argc - n);
	if (argc - n <= 1)
		free_obj(list);
	return (0);
}
