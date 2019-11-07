/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 09:39:36 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/11/07 09:39:37 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_flags(t_flags flags)
{
	ft_printf("flags: ");
	if (flags.list_output == 1)
		ft_printf("-l ");
	if (flags.recursive == 1)
		ft_printf("-R ");
	if (flags.all_files == 1)
		ft_printf("-a ");
	if (flags.reverse == 1)
		ft_printf("-r ");
	if (flags.modif_data_sort == 1)
		ft_printf("-t ");
	ft_printf("\n");
}

void		init_flags(t_flags *flags)
{
	flags->list_output = 0;
	flags->recursive = 0;
	flags->all_files = 0;
	flags->reverse = 0;
	flags->modif_data_sort = 0;
}
