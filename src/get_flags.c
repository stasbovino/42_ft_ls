/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 09:39:28 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/11/07 09:39:29 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	add_flag(t_flags *flags, char f)
{
	if (f == 'l')
		flags->list_output = 1;
	else if (f == 't')
		flags->modif_data_sort = 1;
	else if (f == 'R')
		flags->recursive = 1;
	else if (f == 'a')
		flags->all_files = 1;
	else if (f == 'r')
		flags->reverse = 1;
}

static void	error_options(char f)
{
	ft_printf("./ft_ls: illegal options -- %c\n", f);
	ft_printf("usage: ./ft_ls [-lRart] [file ...]\n");
	exit(1);
}

int			get_flags(int argc, char **argv, t_flags *flags)
{
	int		i;
	int		j;
	char	*s;

	if (argc == 1)
		return (1);
	i = 1;
	while (i < argc && argv[i][0] == '-')
	{
		s = argv[i];
		j = 0;
		while (s[++j])
			if (ft_strchr("lRart", s[j]))
				add_flag(flags, s[j]);
			else
				error_options(s[j]);
		i++;
	}
	return (i);
}
