/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_rights.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 18:59:56 by jmontija          #+#    #+#             */
/*   Updated: 2016/03/02 19:07:31 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	rights[1] = (val & S_IRUSR) ? ('r') : ('-');
	rights[2] = (val & S_IWUSR) ? ('w') : ('-');
	rights[3] = (val & S_IXUSR) ? ('x') : ('-');
	(val & S_ISUID) ? (rights[3] = 's') : 0;
	rights[4] = (val & S_IRGRP) ? ('r') : ('-');
	rights[5] = (val & S_IWGRP) ? ('w') : ('-');
	rights[6] = (val & S_IXGRP) ? ('x') : ('-');
	(val & S_ISGID) ? (rights[6] = 's') : 0;
	rights[7] = (val & S_IROTH) ? ('r') : ('-');
	rights[8] = (val & S_IWOTH) ? ('w') : ('-');
	rights[9] = (val & S_IXOTH) ? ('x') : ('-');
	(val & S_ISVTX) ? (rights[9] = 't') : 0;
	rights[10] = get_acl_attr(grp);
	return (rights);
}
