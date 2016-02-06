/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_lib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 01:19:30 by jmontija          #+#    #+#             */
/*   Updated: 2016/02/06 11:04:44 by jmontija         ###   ########.fr       */
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
		//ft_memdel((void *)file);
		file = file->next;
	}
	grp->first_dir = NULL;
	grp->curr_dir = NULL;
}

t_dir	*init_dir(char *name)
{
	t_dir *new;

	new = (t_dir *)malloc(sizeof(t_dir));
	if (!(new))
		exit(0);
	new->name = SDUP(name);
	new->isopt = false;
	new->next = NULL;
	return (new);
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

char	*manage_time(char *data)
{
	int i = -1;
	while (++i < LEN(data))
	{
		if (data[i] == '\n')
			data[i] = '\0';
	}
	data[i] = '\0';
	data = ft_strchr(data, ' ');
	return (SDUP(data));
}

t_dir	*init_file(struct dirent *file, struct stat buf)
{
	t_dir *new;

	new = (t_dir *)malloc(sizeof(t_dir));
	if (!(new))
		exit(0);
	new->name = SDUP(file->d_name);
	new->last_stat = manage_time(ctime(&buf.st_ctime));
	new->last_access = manage_time(ctime(&buf.st_atime));
	new->last_modif = manage_time(ctime(&buf.st_mtime));
	new->uid = SDUP(getpwuid(buf.st_uid)->pw_name);
	new->gid = SDUP(getgrgid(buf.st_gid)->gr_name);
	new->slink = buf.st_nlink;
	new->size = buf.st_size;
	new->isopt = false;
	new->next = NULL;
	return (new);
}

void	organize_file(t_group *grp, struct dirent *file, struct stat buf)
{
	t_dir	*last_other;
	t_dir	*other;
	t_dir	*new;

	new = init_file(file, buf);
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

t_group	*init_grp(void)
{
	t_group *grp;

	grp = (t_group*)malloc(sizeof(t_group));
	if (!(grp))
		exit(0);
	grp->first_dir = NULL;
	grp->curr_dir = NULL;
	grp->dir_organize = NULL;
	grp->diropen = 0;
	grp->options = (int *)malloc(sizeof(int) * 10);
	grp->root = (char **)malloc(sizeof(char *) * 1);
	grp->root[0] = SDUP(".");
	return (grp);
}
