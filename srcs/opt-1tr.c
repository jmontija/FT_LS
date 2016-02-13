/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt-1tr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 05:16:00 by jmontija          #+#    #+#             */
/*   Updated: 2016/02/12 05:48:15 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*int			ft_cmp_month(char *s1, char *s2)
{
	int i = -1;
	int month_s1 = -1;
	int month_s2 = -1;
	char **month = ft_strsplit("Jan/Feb/Mar/Apr/May/Jun/Jul/Aug/Sep/Oct/Nov/Dec/", '/');

	while (++i < 12)
	{
		(strcmp(s1, month[i]) == 0) ? (month_s1 = i) : 0;
		(strcmp(s2, month[i]) == 0) ? (month_s2 = i) : 0;
	}
	// try -> /opt/local/var/macports/sources/rsync.macports.org/release/tarballs/ports/security
	if (month_s1 > month_s2)
		return (1);
	return (0);
}*/

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

void	opt_test(t_dir	*new, t_dir **first, t_dir **curr)
{
	t_dir	*last_other;
	t_dir	*other;

	if (*curr != NULL)
	{
		other = *first;
		if (new->last_modif_int - other->last_modif_int > 0)
		{
			*first = new;
			new->next = other;
			return ;
		}
		while (other != NULL)
		{
			if (new->last_modif_int - other->last_modif_int > 0)
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

t_dir	*opt_t(t_dir *first)
{
	t_dir *tmp;
	t_dir *tmp2;
	t_dir *curr;

	curr = NULL;
	tmp = NULL;
	while (first)
	{
		tmp2 = copy_file(first);
		opt_test(tmp2, &tmp, &curr);
		first = first->next;
	}
	return (tmp);
}

t_dir	*opt_r(t_dir *first)
{
	t_dir	*last_other = NULL;
	t_dir	*other = first;
	t_dir	*next;

	while (other != NULL)
    {
        next  = other->next;
        other->next = last_other;
        last_other = other;
        other = next;
    }
    return (last_other);
}

void	 sort_launcher(t_group *grp, t_dir **first)
{
	(grp->options[t] == true) ? *first = opt_t(*first) : NULL;
	(grp->options[r] == true) ? *first = opt_r(*first) : NULL;
}