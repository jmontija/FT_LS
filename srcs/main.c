/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 23:36:54 by julio             #+#    #+#             */
/*   Updated: 2016/02/06 07:50:05 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ATTENTION : wrapper.app et authserver sont verrouiller a checker lors de louverture:
// 	sur ces cas ls fait comme si il avait les droits et affiche un fichier vide
//

#include "ft_ls.h"

t_dir	*arg_organizer(int i, t_group *grp, int argc, char **argv)
{
	DIR		*directory;
	t_dir 	*in_order;

	while (++i < argc)
	{
		if (*argv[i] == '-' &&
			grp->diropen == 0 && manage_opt(grp, argv[i]) == true)
			organize_dir(1, grp, argv[i]);
		else
		{
			//warning: avant d'afficher les erreurs il faut les trier lexicographiquemt !
			if (!(directory = opendir(argv[i])))
				is_error(argv[i], "is not an available directory");
			else
			{
				//grp->diropen += 1;
				organize_dir(0, grp, argv[i]);
				closedir(directory);
			}
			grp->diropen += 1;
		}
	}
	in_order = grp->dir_organize;
	grp->dir_organize = NULL;
	grp->curr_dir = NULL;
	return (in_order);
}

void	file_organizer(t_group *grp, t_dir *curr_arg)
{
	DIR		*directory;
	struct dirent	*file;

	directory = opendir(curr_arg->name);
	while ((file = readdir(directory)))
		organize_file(0, grp, file->d_name);
	closedir(directory);
	launcher(grp, curr_arg->name);
	delete_dir(grp);
}

/* essayer de faire un mix entre file_organiser et dir_topen */

int		dir_topen(t_group *grp, t_dir *curr_arg, char ***sub_dir)
{
	DIR				*directory;
	struct dirent	*file;
	char 			*path;
	unsigned char	isdir;
	int 			j;

	j = 0;
	isdir = 4;
	directory = opendir(curr_arg->name);
	//printf("sub_file found\n");
	while ((file = readdir(directory)))
	{
		if (file->d_type == isdir && (file->d_name[0] != '.' ||
			(ft_isalnum(file->d_name[1]) && grp->options[a] == true))) // warning a modifier si le dir est _name
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

void		manage_dir(int i, t_group *grp, int argc, char **argv)
{
	t_dir 	*curr_arg;
	char	**sub_dir = NULL;
	int 	j;

	j = 0;
	sub_dir = (char **)malloc(sizeof(char *) * 1000); // find out pour la taille !
	curr_arg = arg_organizer(i, grp, argc, argv);
	while (curr_arg != NULL)
	{
		if (curr_arg->isopt == false)
		{
			//printf("checking: %s\n", curr_arg->name);
			file_organizer(grp, curr_arg);
			if (grp->options[R] == true)
				j = dir_topen(grp, curr_arg, &sub_dir);
			j > 0 ? manage_dir(-1, grp, j, sub_dir) : 0;
			j = 0;

		}
		else
		{
			printf("option_set: %s\n", curr_arg->name);
		}
		curr_arg = curr_arg->next;
	}
	if (grp->diropen == false)
		manage_dir(-1, grp, 1, grp->root);
}

int		main(int argc, char **argv)
{
	t_group *grp;

	grp = init_grp();
	manage_dir(0, grp, argc, argv);
	return (0);
}
