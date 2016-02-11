/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 05:18:05 by jmontija          #+#    #+#             */
/*   Updated: 2016/02/10 05:18:07 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

char	*manage_rights(char *file, struct stat buf)
{
	char *rights;
	mode_t val;

	rights = NEW(10);
	switch (buf.st_mode & S_IFMT) {
    case S_IFBLK:  rights[0] = 'b';break;
    case S_IFCHR:  rights[0] = 'c';break;
    case S_IFDIR:  rights[0] = 'd';break;
    case S_IFIFO:  rights[0] = 'p';break;
    case S_IFLNK:  rights[0] = 'l';break;
    case S_IFREG:  rights[0] = '-';break;
    case S_IFSOCK: rights[0] = 's';break;
    default:       rights[0] = '?';break;
    }
    val=(buf.st_mode & ~S_IFMT);
	(val & S_IRUSR) ? (rights[1] = 'r' ) : (rights[1] = '-');
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

void	delete_files(t_group *grp)
{
	t_dir *file;
	//t_dir *tmp = NULL;

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
		//tmp = file;
		file = file->next;
		//ft_memdel((void *)tmp);
	}
	grp->first_dir = NULL;
	grp->curr_first_dir = NULL;
}

t_dir	*init_file(t_group *grp, char *file, struct stat buf)
{
	t_dir *new;
	char *actualpath = NEW(1024);
	char *add;
	struct passwd *usr;
	struct group *grpid;
	ssize_t len;

	len	= 0;
	usr	= getpwuid(buf.st_uid);
	grpid = getgrgid(buf.st_gid);
	new = (t_dir *)malloc(sizeof(t_dir));
	if (!(new))
		exit(0);
	if (grp->options[l] && 
		S_ISLNK(buf.st_mode) && ((len = readlink(grp->chemin, actualpath, 1024)) != -1))
	{	
		 actualpath[len] = '\0';
		 add = JOIN(file, " -> ");
		 new->name = JOIN(add, actualpath);

		 REMOVE(&actualpath); REMOVE(&add); REMOVE(&grp->chemin);
	}
	else
		new->name = SDUP(file);
	new->blocks = (int)buf.st_blocks;
	new->rights = manage_rights(file, buf);
	new->last_stat = manage_time(ctime(&buf.st_ctime));
	new->last_access = manage_time(ctime(&buf.st_atime));
	new->last_modif = manage_time(ctime(&buf.st_mtime));
	new->uid = SDUP(usr->pw_name);
	if (grpid != NULL) new->gid = SDUP(grpid->gr_name); else new->gid = SDUP("101");

	new->slink = (int)buf.st_nlink;
	if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
	{
		new->size = (int)major(buf.st_rdev);
		new->size_min = (int)minor(buf.st_rdev);
	}
	else
	{
		new->size = (int)buf.st_size;
		new->size_min = -1;
	}
	new->isopt = false;
	new->next = NULL;
	return (new);
}

void	organize_file(int perm, t_group *grp, char *file, struct stat buf)
{
	t_dir	*new;

	if (perm == 0)
		new = init_file(grp, file, buf);
	else
	{
		new = init_dir(file);
		new->isopt = 2;
	}
	opt_1(new, &grp->first_dir, &grp->curr_first_dir);
}