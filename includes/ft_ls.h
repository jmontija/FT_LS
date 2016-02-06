/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 06:13:10 by jmontija          #+#    #+#             */
/*   Updated: 2016/02/06 07:31:47 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

enum {false, true};
enum {R, t, r, l, a};

typedef int			t_bool;

typedef struct		s_dir
{
	char			*name;
	t_bool			isopt;
	struct s_dir	*next;
}					t_dir;

typedef struct		s_group
{
	t_bool			diropen;
	t_bool			*options;
	char			**root;
	struct s_dir	*dir_organize;
	struct s_dir	*first_dir;
	struct s_dir	*curr_dir;
}					t_group;

t_group		*init_grp(void);
void		is_error(char *who, char *what);
void		organize_dir(int filter, t_group *grp, char *name);
void		organize_file(int filter, t_group *grp, char *name);
void		delete_dir(t_group *grp);
int			manage_opt(t_group *grp, char *opt);
int			isvalid_opt(t_group *grp, char opt);
int			prelauncher(t_group *grp);
int			launcher(t_group *grp, char *opt);
int			allprint(t_group *grp);

#endif
