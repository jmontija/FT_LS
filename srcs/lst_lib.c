/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_lib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 01:19:30 by jmontija          #+#    #+#             */
/*   Updated: 2016/02/08 16:51:07 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*void	delete_dir(t_group *grp)
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
	grp->curr_first_dir = NULL;
}*/

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
	grp->curr_first_dir = NULL;
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
	data = ft_strncpy(NEW(13), data, 13);
	return (SDUP(data));
}

char	*manage_rights(struct stat buf)
{
	char *rights;
	mode_t val;

	rights = NEW(10);
	val=(buf.st_mode & ~S_IFMT);
	if (S_IFDIR & (buf.st_mode)) rights[0] = 'd'; else rights[0] = '-';
	if (val & S_IRUSR) rights[1] = 'r'; else rights[1] = '-';
	if (val & S_IWUSR) rights[2] = 'w'; else rights[2] = '-';
	if (val & S_IXUSR) rights[3] = 'x'; else rights[3] = '-';
	if (val & S_IRGRP) rights[4] = 'r'; else rights[4] = '-';
	if (val & S_IWGRP) rights[5] = 'w'; else rights[5] = '-';
	if (val & S_IXGRP) rights[6] = 'x'; else rights[6] = '-';
	if (val & S_IROTH) rights[7] = 'r'; else rights[7] = '-';
	if (val & S_IWOTH) rights[8] = 'w'; else rights[8] = '-';
	if (val & S_IXOTH) rights[9] = 'x'; else rights[9] = '-';
	return (rights);
}

t_dir	*init_file(char *file, struct stat buf)
{
	t_dir *new;
	struct passwd *usr;
	struct group *grpid;

	usr   = getpwuid(buf.st_uid);
	grpid = getgrgid(buf.st_gid);
	new = (t_dir *)malloc(sizeof(t_dir));
	if (!(new))
		exit(0);
	new->name = SDUP(file);
	new->blocks = (int)buf.st_blocks;
	new->rights = manage_rights(buf);
	new->last_stat = manage_time(ctime(&buf.st_ctime));
	new->last_access = manage_time(ctime(&buf.st_atime));
	new->last_modif = manage_time(ctime(&buf.st_mtime));
	new->uid = SDUP(usr->pw_name);
	if (grpid != NULL) new->gid = SDUP(grpid->gr_name); else new->gid = SDUP("101");
	new->slink = (int)buf.st_nlink;
	new->size = (int)buf.st_size;
	new->isopt = false;
	new->next = NULL;
	return (new);
}

void	organize_file(int perm, t_group *grp, char *file, struct stat buf)
{
	t_dir	*last_other;
	t_dir	*other;
	t_dir	*new;

	//printf("ret = %d\n", perm);
	if (perm == 0)
		new = init_file(file, buf);
	else
	{
		new = init_dir(file);
		new->isopt = 2;
	}
	//printf("YO\n");
	if (grp->curr_first_dir != NULL)
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
		grp->curr_first_dir->next = new;
		//printf("%s becomes last element\n", new->name);
	}
	else
	{
		//printf("entrance: %s becomes first element\n", new->name);
		 grp->first_dir = new;
	}
	grp->curr_first_dir = new;
}

t_group	*init_grp(void)
{
	t_group *grp;

	grp = (t_group*)malloc(sizeof(t_group));
	if (!(grp))
		exit(0);
	grp->first_dir = NULL;
	grp->curr_first_dir = NULL;
	grp->curr_dir = NULL;
	grp->dir_organize = NULL;
	grp->diropen = 0;
	grp->options = (int *)malloc(sizeof(int) * 10);
	grp->root = (char **)malloc(sizeof(char *) * 1);
	grp->root[0] = SDUP(".");
	grp->link_space = 0;
	grp->size_space = 0;
	return (grp);
}
