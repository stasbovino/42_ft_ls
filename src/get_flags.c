#include "ft_ls.h"

static void	set_output_type(t_flags *flags, char f)
{
	if (f == 'l')
		flags->list_output = 1;
	else
		flags->list_output = 0;
	if (f == '1')
		flags->one_file_per_line_output = 1;
	else
		flags->one_file_per_line_output = 0;
	if (f == 'm')
		flags->one_line_output = 1;
	else
		flags->one_line_output = 0;
}

static void	set_sort(t_flags *flags, char f)
{
	if (f == 'S')
	{
		flags->modif_data_sort = 0;
		flags->size_sort = 1;
	}
	else if (flags->size_sort == 1)
		return ;
	else if (f == 't')
		flags->modif_data_sort = 1;
	else if (f == 'u')
		flags->access_data_sort = 1;
	else if (f == 'U')
		flags->creation_data_sort = 1;
}

static void	add_flag(t_flags *flags, char f)
{
	if (f == 'l' || f == '1' || f == 'm')
		set_output_type(flags, f);
	else if (f == 'U' || f == 't' || f == 'u' || f == 'S')
		set_sort(flags, f);
	else if (f == 'R')
		flags->recursive = 1;
	else if (f == 'a')
		flags->all_files = 1;
	else if (f == 'r')
		flags->reverse = 1;
	else if (f == 'G')
		flags->colored_output = 1;
	else if (f == 'A')
		flags->all_files_without_self = 1;
	else if (f == 'g')
		flags->hide_owner = 1;
	else if (f == 'p')
		flags->dir_with_slash = 1;
	else if (f == 'h')
		flags->converted_size = 1;
	else if (f == 'T')
		flags->full_time = 1;
	else if (f == 'n')
		flags->group_name_id = 1;
}

static void	error_options(char f)
{
	ft_printf("./ft_ls: illegal options -- %c\n", f);
	ft_printf("usage: ./ft_ls [-lRartG1mUuSAgphT] [file ...]\n");
	exit(1);
}

int			get_flags(int argc, char **argv, t_flags *flags)
{
	int		i;
	int		j;
	char	*s;

	if (argc == 1)
		return (1);
	i = 0;
	while (++i < argc && argv[i][0] == '-')
	{
		s = argv[i];
		j = 0;
		while (s[++j])
			if (ft_strchr("lRartG1mUuSAgphT", s[j]))
				add_flag(flags, s[j]);
			else
				error_options(s[j]);
	}
	return (i);
}
