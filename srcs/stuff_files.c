/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stuff_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 18:52:53 by jmontija          #+#    #+#             */
/*   Updated: 2016/03/08 22:32:46 by jmontija         ###   ########.fr       */
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
	t_dir			*new;
	struct passwd	*usr;
	struct group	*grpid;

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
	new->gid = (grpid != NULL) ? SDUP(grpid->gr_name) : SDUP("101");
	new->slink = (int)buf.st_nlink;
	new->isopt = false;
	new->next = NULL;
	majmin_file(grp, &new, buf);
	return (new);
}
