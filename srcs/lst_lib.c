/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_lib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 01:19:30 by jmontija          #+#    #+#             */
/*   Updated: 2016/03/08 22:31:33 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	opt_f(t_dir *new, t_dir **first, t_dir **curr)
{
	if (*curr != NULL)
		(*curr)->next = new;
	else
		*first = new;
	*curr = new;
}

int		insert_first(t_dir *new, t_dir **first, t_dir *other)
{
	*first = new;
	new->next = other;
	return (1);
}

int		insert_mid(t_dir *new, t_dir *other, t_dir *last_other)
{
	last_other->next = new;
	new->next = other;
	return (2);
}

t_dir	*copy_file(t_dir *cpy)
{
	t_dir *new;

	new = (t_dir *)malloc(sizeof(t_dir));
	if (!(new) || !cpy)
		return (NULL);
	new->name = SDUP(cpy->name);
	new->isopt = cpy->isopt;
	new->rights = SDUP(cpy->rights);
	new->last_stat = SDUP(cpy->last_stat);
	new->last_access = SDUP(cpy->last_access);
	new->last_modif_int = cpy->last_modif_int;
	new->nano = cpy->nano;
	new->last_modif = SDUP(cpy->last_modif);
	new->uid = SDUP(cpy->uid);
	new->gid = SDUP(cpy->gid);
	new->blocks = cpy->blocks;
	new->slink = cpy->slink;
	new->size = cpy->size;
	new->size_min = cpy->size_min;
	new->next = NULL;
	return (new);
}

t_group	*init_grp(void)
{
	t_group	*grp;
	int		i;

	i = -1;
	grp = (t_group*)malloc(sizeof(t_group));
	if (!(grp))
		exit(0);
	grp->first_dir = NULL;
	grp->curr_first_dir = NULL;
	grp->curr_dir = NULL;
	grp->dir_organize = NULL;
	grp->diropen = 0;
	grp->chemin = NULL;
	grp->ismaj_min = false;
	grp->root = (char **)malloc(sizeof(char *) * 1);
	grp->root[0] = SDUP(".");
	grp->options = (int *)malloc(sizeof(int) * 10);
	while (++i < 10)
		grp->options[i] = false;
	return (grp);
}
