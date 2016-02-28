/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 23:36:54 by julio             #+#    #+#             */
/*   Updated: 2016/02/09 06:17:38 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	create_file_list(t_group *grp, struct dirent *file, t_dir *curr_arg, char ***sub_dir, int *j)
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
		{
			(*sub_dir)[*j] = SDUP(path);
			*j += 1;
		}
	}
	REMOVE(&path);
	REMOVE(&path_before);
}

int	file_organizer(t_group *grp, t_dir *curr_arg, char ***sub_dir)
{
	DIR				*directory;
	struct dirent	*file;
	int				j;

	j = 0;
	if (!(directory = opendir(curr_arg->name)))
	{
		if (grp->diropen > 1)
			ft_putchar('\n');
		perror(curr_arg->name);
		return (j);
	}
	while ((file = readdir(directory)))
		create_file_list(grp, file, curr_arg, sub_dir, &j);
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
					is_error(argv[i], "is not an available directory");
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

void		manage_dir(int i, t_group *grp, int argc, char **argv)
{
	t_dir	*curr_arg;
	//t_dir	*trash;
	char	**sub_dir;
	int		j;

	j = 0;
	sub_dir = (char **)malloc(sizeof(char *) * 10000);
	curr_arg = arg_organizer(i, grp, argc, argv);
	//trash = curr_arg;
	while (curr_arg != NULL)
	{
		j = file_organizer(grp, curr_arg, &sub_dir);
		j > 0 ? manage_dir(-1, grp, j, sub_dir) : 0;
		while (j > 0 && j--)
			REMOVE(&sub_dir[j]);
		j = 0;
		curr_arg = curr_arg->next;
	}
	//delete_dir(trash);
	if (grp->diropen == false)
		manage_dir(-1, grp, 1, grp->root);
}

/* rose = ftls - vert = ls */

int		main(int argc, char **argv)
{
	t_group	*grp;

	grp = init_grp();
	manage_dir(0, grp, argc, argv);
	return (0);
}
