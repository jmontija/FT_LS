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
}

int			ft_cmp_date(char *s1, char *s2)
{
	char *tmp = NULL;
	char *tmp2 = NULL;
	if (strcmp(strrchr(s1, ' '), strrchr(s2, ' ')) < 0)
		return (1);
	tmp = SUB(s1, 1, 3); tmp2 = SUB(s2, 1, 3);
	///printf("same year or sooner %s -> %s\n", tmp, tmp2);
	if (ft_cmp_month(tmp, tmp2) > 0)
	{
		printf("most recent month %s -> %s\n", tmp, tmp2);
		REMOVE(&tmp); REMOVE(&tmp2);
		return (-1);
	}
	printf("same month or sooner %s -> %s\n", tmp, tmp2);
	REMOVE(&tmp); REMOVE(&tmp2);
	tmp = SUB(s1, 5, 2); tmp2 = SUB(s2, 5, 2);
	if (ft_strcmp(tmp, tmp2) > 0)
	{
		printf("most recent day/hours %s -> %s\n", tmp, tmp2);
		REMOVE(&tmp); REMOVE(&tmp2);
		return (-1);
	}
	REMOVE(&tmp); REMOVE(&tmp2);
	return (1);
}*/

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
			//printf("FIRST %s\n", new->name);
			return ;
		}
		while (other != NULL)
		{
			if (new->last_modif_int - other->last_modif_int > 0)
			{
				last_other->next = new;
				new->next = other;
				//printf("BEETWEEN %s\n", new->name);
				return ;
			}
			last_other = other;
			other = other->next;
		}
		//printf("LAST %s\n", new->name);
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
	(grp->options[t] == true) ? *first = opt_t(*first) : NULL;
	(grp->options[r] == true) ? opt_r(first) : NULL;
}