/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 05:18:05 by jmontija          #+#    #+#             */
/*   Updated: 2016/03/02 19:07:42 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	delete_files(t_group *grp)
{
	t_dir	*file;
	//t_dir *trash = NULL;

	file = grp->first_dir;
	while (file != NULL)
	{
		REMOVE(&file->name);
		REMOVE(&file->rights);
		REMOVE(&file->last_stat);
		REMOVE(&file->last_access);
		REMOVE(&file->last_modif);
		REMOVE(&file->uid);
		REMOVE(&file->gid);
		file->slink = 0;
		file->size = 0;
		file->size_min = -1;
		file->blocks = 0;
		//trash = file;
		file = file->next;
		//ft_memdel((void *)trash);
	}
	grp->first_dir = NULL;
	grp->curr_first_dir = NULL;
}

void	organize_file(int perm, t_group *grp, char *file, struct stat buf)
{
	t_dir	*new;

	if (perm == 0)
		new = init_file(grp, file, buf);
	else
	{
		new = init_dir(file, buf);
		new->isopt = 2;
	}
	if (grp->options[f] == true)
		opt_f(new, &grp->first_dir, &grp->curr_first_dir);
	else
		opt_1(new, &grp->first_dir, &grp->curr_first_dir);
}
