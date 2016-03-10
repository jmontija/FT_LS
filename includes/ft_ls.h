/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 06:13:10 by jmontija          #+#    #+#             */
/*   Updated: 2016/03/08 22:52:56 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include "../libft/libft.h"

# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/xattr.h>
# include <sys/acl.h>

# define NEW(x)			(ft_strnew(x))
# define LEN(x)			(ft_strlen(x))
# define SDUP(x)		(ft_strdup(x))
# define SUB(a, b, c)	(ft_strsub(a, b, c))
# define JOIN(a, b)		(ft_strjoin(a, b))
# define REMOVE(x)		(ft_strdel(x))

enum {false, true};
enum {R, t, r, l, a, f, g, d};
typedef int			t_bool;

typedef struct		s_dir
{
	char			*name;
	int				blocks;
	char			*rights;
	char			*last_stat;
	char			*last_access;
	char			*last_modif;
	time_t			last_modif_int;
	long			nano;
	char			*uid;
	char			*gid;
	int				slink;
	int				size;
	int				size_min;
	t_bool			isopt;
	struct s_dir	*next;
}					t_dir;

typedef struct		s_group
{
	t_bool			diropen;
	t_bool			*options;
	t_bool			ismaj_min;
	char			*chemin;
	char			**root;
	struct s_dir	*dir_organize;
	struct s_dir	*curr_dir;
	struct s_dir	*first_dir;
	struct s_dir	*curr_first_dir;
}					t_group;

typedef struct		s_space
{
	int				link_space;
	int				uid_space;
	int				grpid_space;
	int				size_space;
	int				size_min_space;
}					t_space;

t_group				*init_grp(void);
t_dir				*init_dir(char *name, struct stat buf);
t_dir				*init_file(t_group *grp, char *file, struct stat buf);
t_dir				*copy_file(t_dir *tocopy);
void				len_space_slink(t_group *grp, t_space *s_grp);
void				len_space_size(t_group *grp, t_space *s_grp);
void				len_space_size_min(t_group *grp, t_space *s_grp);
void				len_space_uid(t_group *grp, t_space *s_grp);
void				len_space_grpid(t_group *grp, t_space *s_grp);
void				is_error(char *who, char *what);
void				manage_dir(int i, t_group *grp, int argc, char **argv);
void				organize_dir(int f, t_group *g, char *n, struct stat b);
void				organize_file(int p, t_group *g, char *f, struct stat b);
void				delete_dir(t_dir *trash);
void				delete_files(t_group *grp);
void				sort_launcher(t_group *grp, t_dir **first);
int					arg_loop(int i, t_group *grp, int argc, char **argv);
int					insert_first(t_dir *new, t_dir **first, t_dir *other);
int					insert_mid(t_dir *new, t_dir *other, t_dir *last_other);
int					opt_t(t_dir *new, t_dir **first, t_dir **curr);
int					opt_1(t_dir	*new, t_dir **first, t_dir **curr);
void				opt_l(t_group *grp, t_dir *file);
void				opt_f(t_dir *new, t_dir **first, t_dir **curr);
char				*manage_rights(t_group *grp, struct stat buf);
char				*manage_time(char *data);
int					manage_opt(t_group *grp, char *opt);
int					launcher(t_group *grp, char *opt);
int					ft_nblen(int nb);

#endif
