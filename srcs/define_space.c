/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 01:11:02 by julio             #+#    #+#             */
/*   Updated: 2016/02/09 03:23:13 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		len_space_slink(t_group *grp, t_space *s_grp)
{
	t_dir	*test;
	int		i;

	i = 0;
	s_grp->link_space = 0;
	test = grp->first_dir;
	while (test != NULL)
	{
		if (test->slink)
		{
			i = ft_nblen(test->slink);
			if (i > s_grp->link_space)
				s_grp->link_space = i;
		}
		test = test->next;
	}
}

void		len_space_size(t_group *grp, t_space *s_grp)
{
	t_dir	*test;
	int		i;

	i = 0;
	s_grp->size_space = 0;
	test = grp->first_dir;
	while (test != NULL)
	{
		if (test->size)
		{
			i = ft_nblen(test->size);
			if (i > s_grp->size_space)
				s_grp->size_space = i;
		}
		test = test->next;
	}
}

void		len_space_size_min(t_group *grp, t_space *s_grp)
{
	t_dir	*test;
	int		i;

	i = 0;
	s_grp->size_min_space = 0;
	test = grp->first_dir;
	while (test != NULL)
	{
		if (test->size_min)
		{
			i = ft_nblen(test->size_min);
			if (i > s_grp->size_min_space)
				s_grp->size_min_space = i;
		}
		test = test->next;
	}
}

void		len_space_uid(t_group *grp, t_space *s_grp)
{
	t_dir	*test;
	int		i;

	i = 0;
	s_grp->uid_space = 0;
	test = grp->first_dir;
	while (test != NULL)
	{
		if (test->uid)
		{
			i = (int)LEN(test->uid);
			if (i > s_grp->uid_space)
				s_grp->uid_space = i;
		}
		else
			break ;
		test = test->next;
	}
}

void		len_space_grpid(t_group *grp, t_space *s_grp)
{
	t_dir	*test;
	int		i;

	i = 0;
	s_grp->grpid_space = 0;
	test = grp->first_dir;
	while (test != NULL)
	{
		if (test->gid)
		{
			i = (int)LEN(test->gid);
			if (i > s_grp->grpid_space)
				s_grp->grpid_space = i;
		}
		test = test->next;
	}
}

t_space		*define_space(t_group *grp)
{
	t_space *s_grp;

	s_grp = (t_space*)malloc(sizeof(t_space));
	len_space_slink(grp, s_grp);
	len_space_size(grp, s_grp);
	len_space_size_min(grp, s_grp);
	len_space_uid(grp, s_grp);
	len_space_grpid(grp, s_grp);
	return (s_grp);
}
