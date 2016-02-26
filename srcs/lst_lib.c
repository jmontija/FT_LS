/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_lib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 01:19:30 by jmontija          #+#    #+#             */
/*   Updated: 2016/02/09 06:17:05 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

void	init_opt(t_group *grp)
{
	int i;

	i = -1;
	grp->options = (int *)malloc(sizeof(int) * 10);
	while (++i < 10)
		grp->options[i] = false;
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
	grp->chemin = NULL;
	grp->ismaj_min = false;
	grp->root = (char **)malloc(sizeof(char *) * 1);
	grp->root[0] = SDUP(".");
	init_opt(grp);
	return (grp);
}
