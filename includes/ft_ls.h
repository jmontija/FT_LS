#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>

# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "libft.h"

# define NEW(x)			(ft_strnew(x))
# define LEN(x)			(ft_strlen(x))
# define SDUP(x)		(ft_strdup(x))
# define SUB(a, b, c)	(ft_strsub(a, b, c))
# define JOIN(a, b)		(ft_strjoin(a, b))
# define REMOVE(x)		(ft_strdel(x))

typedef int			t_bool;
enum {false, true};

typedef struct		s_dir
{
	char			*name;
	int				type;
	t_bool			print;
	struct s_dir	*next;
}					t_dir;

typedef struct		s_group
{
	t_bool			diropen;
	t_bool			is_R;
	t_bool			is_DIR;
	char			*options;
	char			**sub_dir_organize;
	struct s_dir	*dir_organize;
	struct s_dir	*first_dir;
	struct s_dir	*curr_dir;
}					t_group;

t_group		*init_grp(void);
void		is_error(char *who, char *what);
void		organize_dir(int filter, t_group *grp, char *name);
void		insert(t_group *grp, char *name);
void		delete_dir(t_group *grp);
void		organize_opt(char *options);
int			isvalid_opt(t_group *grp, char opt);
int			prelauncher(t_group *grp);
int			launcher(t_group *grp, char *opt);
int			allprint(t_group *grp);

#endif
