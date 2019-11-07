/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 09:38:32 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/11/07 09:38:33 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_obj		*get_args(int argc, char **argv, int n, t_flags flags)
{
	t_obj *list;

	list = NULL;
	if (n == argc)
		add_obj(&list, create_obj(".", "."), flags);
	else
		while (n < argc)
		{
			if (argv[n][0] == '.' && !argv[n][1])
				add_obj(&list, create_obj(".", "."), flags);
			else
				add_obj(&list, create_obj(argv[n], argv[n]), flags);
			n++;
		}
	return (list);
}
