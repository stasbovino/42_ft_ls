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
int					get_flags(int argc, char **argv, t_flags *flags);

t_obj				*create_obj(char *name, char *full_name);
void				*free_obj(t_obj *src);
void				*add_obj(t_obj **dst, t_obj *new);

t_obj				*get_args(int argc, char **argv, int n);
void				print_args(t_obj *kek);

void				error_stat(char *s);
int					malloc_error(int check);

int					sort_obj(t_obj **obj, t_flags flags);

int					print_dir(t_obj *obj, t_flags flags);
int					print_file(t_obj *list, t_flags flags);
int					recursive_dir(t_obj *obj, t_flags flags);

#endif
