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
	if (flags.colored_output == 1)
		ft_printf("-G ");
	if (flags.one_file_per_line_output == 1)
		ft_printf("-1 ");
	if (flags.one_line_output == 1)
		ft_printf("-m ");
	if (flags.creation_data_sort == 1)
		ft_printf("-U ");
	if (flags.access_data_sort == 1)
		ft_printf("-u ");
	if (flags.size_sort == 1)
		ft_printf("-S ");
	if (flags.hide_owner == 1)
		ft_printf("-g ");
	if (flags.converted_size == 1)
		ft_printf("-h ");
	if (flags.full_time == 1)
		ft_printf("-T ");
	if (flags.group_name_id == 1)
		ft_printf("-n ");
	if (flags.all_files_without_self == 1)
		ft_printf("-A ");
	if (flags.dir_with_slash == 1)
		ft_printf("-p ");
	ft_printf("\n");
}

void		init_flags(t_flags *flags)
{
	flags->list_output = 0;
	flags->recursive = 0;
	flags->all_files = 0;
	flags->reverse = 0;
	flags->modif_data_sort = 0;
	flags->one_file_per_line_output = 0;
	flags->colored_output = 0;
	flags->access_data_sort = 0;
	flags->creation_data_sort = 0;
	flags->all_files_without_self = 0;
	flags->hide_owner = 0;
	flags->one_line_output = 0;
	flags->dir_with_slash = 0;
	flags->size_sort = 0;
	flags->converted_size = 0;
	flags->full_time = 0;
	flags->group_name_id = 0;
}
