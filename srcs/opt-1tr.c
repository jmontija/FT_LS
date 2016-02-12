/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt-tr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 05:16:00 by jmontija          #+#    #+#             */
/*   Updated: 2016/02/10 05:16:02 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	opt_1(t_dir	*new, t_dir **first, t_dir **curr)
{
	t_dir	*last_other;
	t_dir	*other;

	if (*curr != NULL)
	{
		other = *first;
		if (strcmp(new->name, other->name) < 0)
		{
			*first = new;
			new->next = other;
			return ;
		}
		while (other != NULL)
		{
			if (strcmp(new->name, other->name) < 0)
			{
				last_other->next = new;
				new->next = other;
				return ;
			}
			last_other = other;
			other = other->next;
		}
		(*curr)->next = new;
	}
	else
		 *first = new;
	*curr = new;
}

int			ft_cmp_month(char *s1, char *s2)
{
	int i = -1;
	int def_s1 = -1;
	int def_s2 = -1;
	char **month;

	month = ft_strsplit("Jan/Feb/Mar/Apr/May/Jun/Jul/Aug/Sep/Oct/Nov/Dec/", '/');
	while (++i < 12)
	{
		(strcmp(s1, month[i]) == 0) ? (def_s1 = i) : 0;
		(strcmp(s2, month[i]) == 0) ? (def_s2 = i) : 0;
	}
	// try -> /opt/local/var/macports/sources/rsync.macports.org/release/tarballs/ports/security
	return (def_s1 > def_s2 ? 1 : 0);
}

int			ft_cmp_date(char *s1, char *s2)
{
	//
	char *tmp = SUB(s1, 1, 3);
	char *tmp2 = SUB(s2, 1, 3);
	/*if (ft_strcmp(strrchr(s1, ' '), strrchr(s2, ' ')) > 0)
		return (0);*/
	printf("%s -> %s\n", tmp, tmp2);
	if (ft_cmp_month(tmp, tmp2) > 0)
		return (0);
	REMOVE(&tmp); REMOVE(&tmp2);
	tmp = SUB(s1, 5, 8); tmp2 = SUB(s2, 5, 8);
	//printf("%s -> %s\n", tmp, tmp2);
	/*if (ft_strcmp(tmp, tmp2) > 0)
		return (0);*/
	//REMOVE(&tmp); REMOVE(&tmp2);
	return (1);
}

t_dir		*sort_dates(t_dir *tmp, t_dir *lst)
{
	t_dir		*tmp2;

	if (!lst)
		return (tmp);
	if (!(ft_cmp_date(tmp->last_modif, lst->last_modif)))
	{
		tmp->next = lst;
		return (tmp);
	}
	tmp2 = lst;
	while (lst->next && ft_cmp_date(tmp->last_modif, (lst->next)->last_modif))
		lst = lst->next;
	if (lst->next)
		tmp->next = lst->next;
	lst->next = tmp;
	return (tmp2);
}

void	opt_t(t_dir **first)
{
	t_dir *tmp;
	t_dir *tmp2;

	tmp = NULL;
	while (*first)
	{
		tmp2 = copy_file(*first);
		tmp = sort_dates(tmp2, tmp);
		*first = (*first)->next;
	}
	*first = tmp;
}

void	opt_r(t_dir **first)
{
	t_dir	*last_other = NULL;
	t_dir	*other = *first;
	t_dir	*next;

	while (other != NULL)
    {
        next  = other->next;  
        other->next = last_other;   
        last_other = other;
        other = next;
    }
    *first = last_other;
}

void	 sort_launcher(t_group *grp, t_dir **first)
{
	(grp->options[t] == true) ? opt_t(first) : NULL;
	(grp->options[r] == true) ? opt_r(first) : NULL;
}