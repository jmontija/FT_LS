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

// ATTENTION : wrapper.app et authserver sont verrouiller a checker lors de louverture:
// 	sur ces cas ls fait comme si il avait les droits et affiche un fichier vide

#include "ft_ls.h"
#include <errno.h>

void	file_organizer(t_group *grp, t_dir *curr_arg)
{
	DIR				*directory;
	struct dirent	*file;
	struct stat		buf;
	char			*path_before;
	char			*path;
	int 			ret;

	if (!(directory = opendir(curr_arg->name)))
	{
		perror("WTF!");
		exit(0);
	}
	while ((file = readdir(directory)))
	{
		path_before = JOIN(curr_arg->name, "/");
		path = JOIN(path_before, file->d_name);
		ret = lstat(path, &buf);
		//printf("retfile = %d %s\n", ret, path);
		grp->chemin = SDUP(path);
		REMOVE(&path); REMOVE(&path_before);
		organize_file(ret, grp, file->d_name, buf);
	}
	closedir(directory);
	launcher(grp, curr_arg->name);
	delete_dir(grp);
}

void	show_file(t_group *grp, int dir_opened)
{
	// fichier apeller par les arguments dans le shell
	if (grp->curr_first_dir != NULL)
	{
		launcher(grp, NULL);
		delete_dir(grp);
		if (dir_opened > 0)
			ft_putchar('\n');
	}
}

void	define_status(t_group *grp, char *arg, struct stat buf)
{
	grp->chemin = SDUP(arg);
	if (S_ISREG(buf.st_mode) || S_ISLNK(buf.st_mode))
		organize_file(0, grp, arg, buf);
	else
	{
		if (grp->diropen > 0)
			ft_putchar('\n');
		perror(arg);
	}
}

/* essayer de faire un mix entre file_organiser et dir_topen */

int		dir_topen(t_group *grp, t_dir *curr_arg, char ***sub_dir)
{
	DIR				*directory;
	struct dirent	*file;
	//struct stat		buf;
	char 			*path;
	int 			j;
	//	int 			ret;

	j = 0;
	//ret = 0;
	//if (directory = opendir(curr_arg->name);
	if (!(directory = opendir(curr_arg->name)))
	{
		perror("WTF!");
		exit(0);
	}	
	while ((file = readdir(directory)))
	{
		//ret = lstat(file->d_name, &buf)
		if (file->d_type == DT_DIR && (file->d_name[0] != '.' ||
			(file->d_name[1] && file->d_name[1] != '.' && grp->options[a] == true)))
		{
			//printf("sub_dir found %s\n", file->d_name);
			path = JOIN(curr_arg->name, "/");
			(*sub_dir)[j] = JOIN(path, file->d_name);
			REMOVE(&path);
			j++;
		}
	}
	closedir(directory);
	//printf("Sub_diR->%s/ = %d\n", curr_arg->name, j);
	return (j);
}

t_dir	*arg_organizer(int i, t_group *grp, int argc, char **argv)
{
	DIR				*directory;
	t_dir 			*in_order;
	struct stat		buf;
	int 			ret;
	int				dir_opened = 0;
	char			*error;

	while (++i < argc)
	{
		if (*argv[i] == '-' && grp->diropen == 0 )
			manage_opt(grp, argv[i]);
		else
		{
			// warning: avant d'afficher les erreurs il faut les trier lexicographiquemt !
			if (!(directory = opendir(argv[i])))
			{
				if ((ret = lstat(argv[i], &buf)) < 0)
					is_error(argv[i], "is not an available directory");
				else
					define_status(grp, argv[i], buf);	
			}
			else
			{
				organize_dir(0, grp, argv[i]);
				closedir(directory);
				dir_opened += 1;
			}
			grp->diropen += 1;
		}
	}
	show_file(grp, dir_opened);
	in_order = grp->dir_organize;
	grp->dir_organize = NULL;
	grp->curr_dir = NULL;
	return (in_order);
}

void		manage_dir(int i, t_group *grp, int argc, char **argv)
{
	t_dir 	*curr_arg;
	char	**sub_dir = NULL;
	int 	j;

	j = 0;
	sub_dir = (char **)malloc(sizeof(char *) * 10000); // find out pour la taille !
	curr_arg = arg_organizer(i, grp, argc, argv);
	while (curr_arg != NULL)
	{
		//printf("checking: %s\n", curr_arg->name);
		file_organizer(grp, curr_arg);
		if (grp->options[R] == true)
			j = dir_topen(grp, curr_arg, &sub_dir);
		j > 0 ? manage_dir(-1, grp, j, sub_dir) : 0;
		while (j--)
			REMOVE(&sub_dir[j]);
		j = 0;
		curr_arg = curr_arg->next;
	}
	if (grp->diropen == false)
		manage_dir(-1, grp, 1, grp->root);
}

int		main(int argc, char **argv)
{
	t_group *grp = NULL;
	int i = 0;

	grp = init_grp();
	manage_dir(i, grp, argc, argv);
	return (0);
}
