/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 19:26:46 by jmontija          #+#    #+#             */
/*   Updated: 2016/03/08 22:32:04 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*create_file_list(t_group *grp, struct dirent *file, t_dir *curr_arg)
{
	struct stat		buf;
	char			*path_before;
	char			*path;
	int				ret;

	path_before = JOIN(curr_arg->name, "/");
	path = JOIN(path_before, file->d_name);
	ret = lstat(path, &buf);
	grp->chemin = SDUP(path);
	organize_file(ret, grp, file->d_name, buf);
	if (grp->options[R] == true && (file->d_name[0] != '.' ||
	(file->d_name[1] && file->d_name[1] != '.' && grp->options[a] == true)))
	{
		if (S_ISDIR(buf.st_mode))
			return (path);
	}
	REMOVE(&path);
	REMOVE(&path_before);
	return (NULL);
}

int		file_organizer(t_group *grp, t_dir *curr_arg, char ***sub_dir)
{
	DIR				*directory;
	struct dirent	*file;
	char			*path;
	int				j;

	j = 0;
	if (!(directory = opendir(curr_arg->name)))
	{
		grp->diropen > 1 ? ft_putchar('\n') : 0;
		perror(curr_arg->name);
		return (j);
	}
	while ((file = readdir(directory)))
	{
		if ((path = create_file_list(grp, file, curr_arg)) != NULL)
		{
			(*sub_dir)[j] = SDUP(path);
			j++;
		}
	}
	closedir(directory);
	sort_launcher(grp, &grp->first_dir);
	launcher(grp, curr_arg->name);
	delete_files(grp);
	return (j);
}

void	show_file(t_group *grp, int dir_opened)
{
	if (grp->curr_first_dir != NULL)
	{
		sort_launcher(grp, &grp->first_dir);
		launcher(grp, NULL);
		delete_files(grp);
		if (dir_opened > 0)
			ft_putchar('\n');
	}
}

t_dir	*arg_organizer(int i, t_group *grp, int argc, char **argv)
{
	t_dir	*in_order;
	int		dir_opened;

	dir_opened = arg_loop(i, grp, argc, argv);
	show_file(grp, dir_opened);
	sort_launcher(grp, &grp->dir_organize);
	in_order = grp->dir_organize;
	grp->dir_organize = NULL;
	grp->curr_dir = NULL;
	return (in_order);
}

void	manage_dir(int i, t_group *grp, int argc, char **argv)
{
	t_dir	*curr_arg;
	t_dir	*trash;
	char	**sub_dir;
	int		j;

	j = 0;
	sub_dir = (char **)malloc(sizeof(char *) * 10000);
	curr_arg = arg_organizer(i, grp, argc, argv);
	trash = curr_arg;
	while (curr_arg != NULL)
	{
		j = file_organizer(grp, curr_arg, &sub_dir);
		j > 0 ? manage_dir(-1, grp, j, sub_dir) : 0;
		while (j > 0 && j--)
			REMOVE(&sub_dir[j]);
		j = 0;
		curr_arg = curr_arg->next;
	}
	delete_dir(trash);
	if (grp->diropen == false)
		manage_dir(-1, grp, 1, grp->root);
}
