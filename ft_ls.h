#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"

/*
** dir func
*/

# include <dirent.h>

/*
** getpwuid
*/

# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>

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

/*
** bonuses
*/

	char colored_output; // -G
	char one_file_per_line_output; // -1
	char one_line_output; // -m

	char creation_data_sort; // -U
	char access_data_sort; // -u
	char size_sort; // -S

	char hide_owner; // -g
	char converted_size; // -h
	char full_time; // -T
	char group_name_id; // -n

	char all_files_without_self; // -A
	char dir_with_slash; // -p
}					t_flags;

void				print_flags(t_flags flags);
int					get_flags(int argc, char **argv, t_flags *flags);

/*
typedef struct		s_data
{
	int link;
	int owner;
	int group;
	int fileSize;
	int date_month;
	int date_day;
	int date_hour;
	int date_minute;
	int date_year;
	int user_id;
	int group_id;
	int major;
	int minor;
}					t_data;


typedef struct		s_date
{
	char *month;
	char *day;
	char *hour;
	char *minute;
	char *year;
	unsigned long long mtv_sec;
	unsigned long long mtv_nsec;
	unsigned long long atv_sec;
	unsigned long long atv_nsec;
	unsigned long long ctv_sec;
	unsigned long long ctv_nsec;
	unsigned long long birthtv_sec;
	unsigned long long birthtv_nsec;
}					t_date;

typedef struct		s_files
{
	char *modes;
	long link;
	char *owner;
	unsigned int user_id;
	char *group;
	unsigned int group_id;
	long size;
	t_date date;
	char *name;
	int is_dir_info;
	long major;
	long minor;
	int is_chr_or_blk;
	int is_link;
	char *linked_to;
	int has_nonprintable_chars;
	char *display_name;
	int status;
	struct s_files *next;
	struct stat f; // Since I'm passing this I don't need to do stuffs like is_link or is_chr_or_blk
}					t_files;

typedef struct s_dirs {
  char *name;
  int status;
  t_files *files;
  t_files *self;
  t_format format;
  int       is_default;
  int       is_unreadable;
  int       total_blocks;
  struct s_dirs *sub_dirs;
  struct s_dirs *next;
  int file_count;
  int max_file_len;
  t_date date;
  int is_subdir;
  char *display_name;
  int has_chr_or_blk;
  int has_valid_files;
} t_dirs;

typedef union u_etarget {
  char flag;
  char *file;
} t_etarget;

typedef union u_entries {
  t_files *files;
  char **file_names;
} t_entries;e
*/
#endif
