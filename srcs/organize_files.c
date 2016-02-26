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

char	*display_years(struct stat buf, char *data)
{
	time_t	act_time;
	time_t	s_month;
	char	*years;
	char	*md;

	act_time = time(0);
	s_month = act_time - 15724800;
	years = NULL;
	md = NULL;
	if (buf.st_mtime <= s_month)
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
	size_t	i;

	i = -1;
	while (++i < LEN(data))
	{
		if (data[i] == '\n')
			data[i] = '\0';
	}
	data = ft_strchr(data, ' ');
	return (SDUP(data));
}

char	get_acl_attr(t_group *grp)
{
	char		rights;
	ssize_t		buflen;
	acl_t		acl;

	buflen = 0;
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

char	get_type(struct stat buf)
{
	char type;

	S_ISBLK(buf.st_mode) ? type = 'b' : 0;
	S_ISCHR(buf.st_mode) ? type = 'c' : 0;
	S_ISDIR(buf.st_mode) ? type = 'd' : 0;
	S_ISFIFO(buf.st_mode) ? type = 'p' : 0;
	S_ISLNK(buf.st_mode) ? type = 'l' : 0;
	S_ISREG(buf.st_mode) ? type = '-' : 0;
	S_ISSOCK(buf.st_mode) ? type = 's' : 0;
	return (type);
}

char	*manage_rights(t_group *grp, struct stat buf)
{
	char		*rights;
	mode_t		val;

	rights = NEW(11);
	val = (buf.st_mode & ~S_IFMT);
	rights[0] = get_type(buf);
	(val & S_IRUSR) ? (rights[1] = 'r') : (rights[1] = '-');
	(val & S_IWUSR) ? (rights[2] = 'w') : (rights[2] = '-');
	(val & S_IXUSR) ? (rights[3] = 'x') : (rights[3] = '-');
	(val & S_ISUID) ? (rights[3] = 's') : 0;
	(val & S_IRGRP) ? (rights[4] = 'r') : (rights[4] = '-');
	(val & S_IWGRP) ? (rights[5] = 'w') : (rights[5] = '-');
	(val & S_IXGRP) ? (rights[6] = 'x') : (rights[6] = '-');
	(val & S_ISGID) ? (rights[6] = 's') : 0;
	(val & S_IROTH) ? (rights[7] = 'r') : (rights[7] = '-');
	(val & S_IWOTH) ? (rights[8] = 'w') : (rights[8] = '-');
	(val & S_IXOTH) ? (rights[9] = 'x') : (rights[9] = '-');
	(val & S_ISVTX) ? (rights[9] = 't') : 0;
	rights[10] = get_acl_attr(grp);
	return (rights);
}

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

char	*name_file(t_group *grp, char *file, struct stat buf)
{
	char	*actualpath;
	char	*add;
	char	*name;
	ssize_t	len;

	actualpath = NEW(1024);
	name = NULL;
	len = 0;
	if (grp->options[l] &&
		S_ISLNK(buf.st_mode) &&
		((len = readlink(grp->chemin, actualpath, 1024)) != -1))
	{
		actualpath[len] = '\0';
		add = JOIN(file, " -> ");
		name = JOIN(add, actualpath);
		REMOVE(&actualpath);
		REMOVE(&add);
		REMOVE(&grp->chemin);
	}
	else
		name = SDUP(file);
	return (name);
}

void	majmin_file(t_group *grp, t_dir **new, struct stat buf)
{
	if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
	{
		if (grp->ismaj_min == false)
			grp->ismaj_min = true;
		(*new)->size = (int)major(buf.st_rdev);
		(*new)->size_min = (int)minor(buf.st_rdev);
	}
	else
	{
		grp->ismaj_min = false;
		(*new)->size = (int)buf.st_size;
		(*new)->size_min = -1;
	}
}

t_dir	*init_file(t_group *grp, char *file, struct stat buf)
{
	t_dir	*new;
	struct passwd *usr;
	struct group *grpid;

	usr = getpwuid(buf.st_uid);
	grpid = getgrgid(buf.st_gid);
	new = (t_dir *)malloc(sizeof(t_dir));
	if (!(new))
		exit(0);
	new->name = name_file(grp, file, buf);
	new->blocks = (int)buf.st_blocks;
	new->rights = manage_rights(grp, buf);
	new->last_stat = manage_time(ctime(&buf.st_ctime));
	new->last_access = manage_time(ctime(&buf.st_atime));
	new->last_modif_int = buf.st_mtime;
	new->last_modif = manage_time(ctime(&buf.st_mtime));
	new->last_modif = display_years(buf, new->last_modif);
	new->uid = SDUP(usr->pw_name);
	(grpid != NULL) ? (new->gid = SDUP(grpid->gr_name)) : (new->gid = SDUP("101"));
	new->slink = (int)buf.st_nlink;
	new->isopt = false;
	new->next = NULL;
	majmin_file(grp, &new, buf);
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
	if (grp->options[f] == true)
		opt_f(new, &grp->first_dir, &grp->curr_first_dir);
	else
		opt_1(new, &grp->first_dir, &grp->curr_first_dir);
}
