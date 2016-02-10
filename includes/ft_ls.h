/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 06:13:10 by jmontija          #+#    #+#             */
/*   Updated: 2016/02/09 03:31:39 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>

# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include "libft.h"

# define NEW(x)			(ft_strnew(x))
# define LEN(x)			(ft_strlen(x))
# define SDUP(x)		(ft_strdup(x))
# define SUB(a, b, c)	(ft_strsub(a, b, c))
# define JOIN(a, b)		(ft_strjoin(a, b))
# define REMOVE(x)		(ft_strdel(x))

enum {false, true};
enum {R, t, r, l, a};

typedef int			t_bool;

typedef struct		s_dir
{
	char			*name;
	int				blocks;
	char			*rights;
	char			*last_stat;
	char			*last_access;
	char			*last_modif;
	char			*uid;
	char			*gid;
	int 			slink;
	int				size;
	t_bool			isopt;
	struct s_dir	*next;
}					t_dir;

typedef struct		s_group
{
	t_bool			diropen;
	t_bool			*options;
	char			*chemin;
	char			**root;
	struct s_dir	*dir_organize;
	struct s_dir	*curr_dir;
	struct s_dir	*first_dir;
	struct s_dir	*curr_first_dir;

}					t_group;

typedef struct		s_space
{
	int		link_space;
	int		uid_space;
	int		grpid_space;
	int		size_space;
}					t_space;

t_group		*init_grp(void);
t_space		*define_space(t_group *grp, t_dir *file);
void		is_error(char *who, char *what);
void		organize_dir(int filter, t_group *grp, char *name);
void		organize_file(int perm, t_group *grp, char *file, struct stat buf);
void		delete_dir(t_group *grp);
void		delete_files(t_group *grp);
void		opt_l(t_group *grp, t_dir *file);
int			ft_nblen(int nb);
int			manage_opt(t_group *grp, char *opt);
int			isvalid_opt(t_group *grp, char opt);
int			prelauncher(t_group *grp);
int			launcher(t_group *grp, char *opt);
int			allprint(t_group *grp);

#endif
