/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 05:18:05 by jmontija          #+#    #+#             */
/*   Updated: 2016/02/12 05:50:14 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char 	*display_years(struct stat buf, char *data)
{
	time_t	act_time = time(0);
	time_t 	s_month = 15778800;
	char 	*years = NULL;
	char 	*md = NULL;

	if (buf.st_mtime < (act_time - s_month))
	{
		years = strrchr(data, ' ');
		md = SUB(data, 0, 7);
		data = ft_strjoin(md, " ");
		data = ft_strjoin(data, years);
	}
	else
		data = ft_strncpy(NEW(13), data, 13);
	return (data);
}

char	*manage_time(char *data)
{
	size_t i = -1;

	while (++i < LEN(data))
	{
		if (data[i] == '\n')
			data[i] = '\0';
	}
	data = ft_strchr(data, ' ');
	return (SDUP(data));
}

char	get_acl_attr(t_group *grp, mode_t val)
{
	char		rights;
	ssize_t		buflen;
	acl_t		acl;

	buflen = 0;
	if (val & S_ISVTX)
		rights = 't';
	else
		(val & S_IXOTH) ? (rights = 'x') : (rights = '-');
	buflen = listxattr(grp->chemin, NULL, 0, 0);
	acl = acl_get_file(grp->chemin, ACL_TYPE_EXTENDED);
	if (buflen > 0)
		rights = '@';
	else if (acl)
		rights = '+';
	else
		rights = ' ';
	return (rights);
}

char	*manage_rights(t_group *grp, struct stat buf)
{
	char 		*rights;
	mode_t		val;

	rights = NEW(10);
	S_ISBLK(buf.st_mode)  ? rights[0] = 'b' : 0;
	S_ISCHR(buf.st_mode)  ? rights[0] = 'c' : 0;
	S_ISDIR(buf.st_mode)  ? rights[0] = 'd' : 0;
	S_ISFIFO(buf.st_mode) ? rights[0] = 'p' : 0;
	S_ISLNK(buf.st_mode)  ? rights[0] = 'l' : 0;
	S_ISREG(buf.st_mode)  ? rights[0] = '-' : 0;
	S_ISSOCK(buf.st_mode) ? rights[0] = 's' : 0;
    val=(buf.st_mode & ~S_IFMT);
	(val & S_IRUSR) ? (rights[1] = 'r') : (rights[1] = '-');
	(val & S_IWUSR) ? (rights[2] = 'w') : (rights[2] = '-');
	(val & S_IXUSR) ? (rights[3] = 'x') : (rights[3] = '-');
	(val & S_IRGRP) ? (rights[4] = 'r') : (rights[4] = '-');
	(val & S_IWGRP) ? (rights[5] = 'w') : (rights[5] = '-');
	(val & S_IXGRP) ? (rights[6] = 'x') : (rights[6] = '-');
	(val & S_IROTH) ? (rights[7] = 'r') : (rights[7] = '-');
	(val & S_IWOTH) ? (rights[8] = 'w') : (rights[8] = '-');
	(val & S_IXOTH) ? (rights[9] = 'x') : (rights[9] = '-');
	rights[10] = get_acl_attr(grp, val);
	return (rights);
}

void	delete_files(t_group *grp)
{
	t_dir *file;
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
	new->rights = manage_rights(grp, buf);
	new->last_stat = manage_time(ctime(&buf.st_ctime));
	new->last_access = manage_time(ctime(&buf.st_atime));
	new->last_modif_int = buf.st_mtime;
	new->last_modif = manage_time(ctime(&buf.st_mtime));
	new->last_modif = display_years(buf, new->last_modif);
	new->uid = SDUP(usr->pw_name);
	if (grpid != NULL) new->gid = SDUP(grpid->gr_name); else new->gid = SDUP("101");

	new->slink = (int)buf.st_nlink;
	if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
	{
		if (grp->ismaj_min == false)
			grp->ismaj_min = true;
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
		new = init_dir(file, buf);
		new->isopt = 2;
	}
	opt_1(new, &grp->first_dir, &grp->curr_first_dir);
}