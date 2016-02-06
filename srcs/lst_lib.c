/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_lib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 01:19:30 by jmontija          #+#    #+#             */
/*   Updated: 2016/02/06 01:54:08 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	delete_dir(t_group *grp)
{
	t_dir *file;

	file = grp->first_dir;
	while (file != NULL)
	{
		if (file->name)
			REMOVE(&file->name);
		ft_memdel((void *)file);
		file = file->next;
	}
	grp->first_dir = NULL;
	grp->curr_dir = NULL;
}

t_dir	*init_dir(char *name)
{
	t_dir *file;

	file = (t_dir *)malloc(sizeof(t_dir));
	if (!(file))
		exit(0);
	file->name = SDUP(name);
	file->isopt = false;
	file->print = false;
	file->next = NULL;
	return (file);
}

void	organize_dir(int isopt, t_group *grp, char *name)
{
	t_dir	*last_other;
	t_dir	*other;
	t_dir	*new;

	new = init_dir(name);
	new->isopt = isopt;
	if (grp->curr_dir != NULL)
	{
		other = grp->dir_organize;
		if (strcmp(new->name, other->name) < 0 || isopt)
		{
			//printf("%s becomes first element\n", new->name);
			grp->dir_organize = new;
			new->next = other;
			return ;
		}
		while (other != NULL)
		{
			if (strcmp(new->name, other->name) < 0)
			{
				//printf("insert %s between %s & %s\n", new->name, last_other->name, other->name);
				last_other->next = new;
				new->next = other;
				return ;
			}
			last_other = other;
			other = other->next;
		}
		grp->curr_dir->next = new;
		//printf("%s becomes last element\n", new->name);
	}
	else
	{
		//printf("entrance: %s becomes first element\n", new->name);
		 grp->dir_organize = new;
	}
	grp->curr_dir = new;
}

void	organize_file(int isfile, t_group *grp, char *name)
{
	t_dir	*last_other;
	t_dir	*other;
	t_dir	*new;

	new = init_dir(name);
	new->isopt = isfile;
	//printf("FILE %s\n", name);
	if (grp->curr_dir != NULL)
	{
		other = grp->first_dir;
		if (strcmp(new->name, other->name) < 0)
		{
			//printf("%s becomes first element\n", new->name);
			grp->first_dir = new;
			new->next = other;
			return ;
		}
		while (other != NULL)
		{
			if (strcmp(new->name, other->name) < 0)
			{
				//printf("insert %s between %s & %s\n", new->name, last_other->name, other->name);
				last_other->next = new;
				new->next = other;
				return ;
			}
			last_other = other;
			other = other->next;
		}
		grp->curr_dir->next = new;
		//printf("%s becomes last element\n", new->name);
	}
	else
	{
		//printf("entrance: %s becomes first element\n", new->name);
		 grp->first_dir = new;
	}
	grp->curr_dir = new;
}



void	insert(t_group *grp, char *name)
{
	t_dir	*new;

	new = init_dir(name);
	if (grp->curr_dir != NULL)
		grp->curr_dir->next = new;
	else
		grp->first_dir = new;
	grp->curr_dir = new;
}

t_group	*init_grp(void)
{
	t_group *grp;

	grp = (t_group*)malloc(sizeof(t_group));
	if (!(grp))
		exit(0);
	grp->first_dir = NULL;
	grp->curr_dir = NULL;
	grp->dir_organize = NULL;
	grp->sub_dir_organize = NULL;
	grp->options = NULL;
	grp->is_R = false;
	grp->diropen = 0;
	return (grp);
}
