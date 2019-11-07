/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_link_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 09:40:18 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/11/07 09:42:04 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			get_only_path(char *s)
{
	int i;
	int last;

	i = -1;
	last = 0;
	while (s[++i])
		if (s[i] == '/')
			last = i;
	return (last + 1);
}

int			get_link_data(t_obj *new)
{
	char *s;

	s = ft_strnew(256);
	readlink(new->full_name, s, 256);
	if (stat(new->full_name, &new->link_data) == -1)
	{
		errno = 0;
		return (0);
	}
	new->link_name = ft_strdup(s);
	new->full_link_name = ft_strjoin(ft_strsub(new->full_name, 0,
				get_only_path(new->full_name)), new->link_name);
	free(s);
	if (S_ISDIR(new->link_data.st_mode))
		new->link_case = 1;
	return (0);
}
