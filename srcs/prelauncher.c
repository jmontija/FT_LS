/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prelauncher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 02:12:25 by jmontija          #+#    #+#             */
/*   Updated: 2016/02/05 18:49:46 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_oread(t_group *grp, char *opt)
{
	DIR				*directory;
	struct dirent	*file;

	grp->curr_dir = NULL;
	directory = opendir(opt);
	while ((file = readdir(directory)))
		insert(grp, file->d_name);
	closedir(directory);
	return (1);
}

/*int		prelauncher(t_group *grp, char *dir)
{
	t_dir	*directory;

	directory = grp->dir_organize;
	while (directory != NULL)	//{
		//ft_oread(grp, directory->name);
		//ft_putnbr(directory->type);
		launcher(grp, directory->name);
		delete_dir(grp);
		//directory = directory->next;
	//}
	//return(0);
}*/
