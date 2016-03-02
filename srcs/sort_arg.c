/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 19:12:18 by jmontija          #+#    #+#             */
/*   Updated: 2016/03/02 20:30:19 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	define_status(t_group *grp, char *arg, struct stat buf)
{
	grp->chemin = SDUP(arg);
	if (S_ISREG(buf.st_mode) || S_ISLNK(buf.st_mode) || grp->options[d] == true)
		organize_file(0, grp, arg, buf);
	else if (S_ISDIR(buf.st_mode))
		organize_dir(2, grp, arg, buf);
}

int		arg_dir(t_group *grp, struct stat buf, DIR *directory, char *arg)
{
	if (lstat(arg, &buf) < 0)
		is_error(arg, "is not an available directory");
	organize_dir(0, grp, arg, buf);
	closedir(directory);
	return (1);
}

int		arg_loop(int i, t_group *grp, int argc, char **argv)
{
	DIR				*directory;
	struct stat		buf;
	int				ret;
	int				dir_opened;

	dir_opened = 0;
	while (++i < argc)
	{
		if (*argv[i] == '-' && grp->diropen == 0)
			manage_opt(grp, argv[i]);
		else
		{
			if (!(directory = opendir(argv[i])) || grp->options[d] == true)
			{
				if ((ret = lstat(argv[i], &buf)) < 0)
					is_error(argv[i], "is not an available files");
				else
					define_status(grp, argv[i], buf);
			}
			else
				dir_opened = arg_dir(grp, buf, directory, argv[i]);
			grp->diropen += 1;
		}
	}
	return (dir_opened);
}
