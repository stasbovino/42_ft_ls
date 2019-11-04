#ifndef FT_LS_H
# define FT_LS_H

#include <sys/ioctl.h>
# include "libft.h"
# include <stdio.h>
# include <errno.h>

/*
** dir func
*/

# include <dirent.h>

/*
** getpwuid
*/

# include <sys/types.h>
# include <pwd.h>

/*
** getgrgid
*/

# include <grp.h>

/*
** listxattr getxattr
*/

# include <sys/xattr.h>

/*
** time ctime
*/

# include <time.h>

/*
**	stat lstat
*/

# include <sys/stat.h>

typedef struct		s_flags
{
	char list_output; // -l
	char recursive; // -R
	char all_files; // -a
	char reverse; // -r
	char modif_data_sort; // -t
}					t_flags;

typedef struct		s_queue
{
	char			*name;
	struct s_queue	*next;
}					t_queue;

typedef struct		s_obj
{
	char			*name;
	char			*full_name;
	struct stat		buf;
	struct s_obj	*next;
}					t_obj;

void				init_flags(t_flags *flags);
void				print_flags(t_flags flags);

#endif
