/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_1tr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 05:16:00 by jmontija          #+#    #+#             */
/*   Updated: 2016/03/02 19:12:50 by jmontija         ###   ########.fr       */
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

int		opt_1(t_dir *new, t_dir **first, t_dir **curr)
{
	t_dir	*last_other;
	t_dir	*other;

	if (*curr != NULL)
	{
		other = *first;
		if (strcmp(new->name, other->name) < 0)
			return (insert_first(new, first, other));
		while (other != NULL)
		{
			if (strcmp(new->name, other->name) < 0)
				return (insert_mid(new, other, last_other));
			last_other = other;
			other = other->next;
		}
		(*curr)->next = new;
	}
	else
		*first = new;
	*curr = new;
	return (1);
}

int		opt_t(t_dir *new, t_dir **first, t_dir **curr)
{
	t_dir	*last_other;
	t_dir	*other;

	if (*curr != NULL)
	{
		other = *first;
		if (new->last_modif_int - other->last_modif_int > 0)
			return (insert_first(new, first, other));
		while (other != NULL)
		{
			if (new->last_modif_int - other->last_modif_int > 0)
				return (insert_mid(new, other, last_other));
			last_other = other;
			other = other->next;
		}
		(*curr)->next = new;
	}
	else
		*first = new;
	*curr = new;
	return (1);
}

t_dir	*opt_tsort(t_dir *first)
{
	t_dir *first_new;
	t_dir *cpy;
	t_dir *curr;

	curr = NULL;
	first_new = NULL;
	while (first)
	{
		cpy = copy_file(first);
		opt_t(cpy, &first_new, &curr);
		first = first->next;
	}
	return (first_new);
}

t_dir	*opt_r(t_dir *first)
{
	t_dir	*last_other;
	t_dir	*other;
	t_dir	*next;

	last_other = NULL;
	other = first;
	while (other != NULL)
	{
		next = other->next;
		other->next = last_other;
		last_other = other;
		other = next;
	}
	return (last_other);
}

void	sort_launcher(t_group *grp, t_dir **first)
{
	if (grp->options[f] == true)
		return ;
	(grp->options[t] == true) ? *first = opt_tsort(*first) : NULL;
	(grp->options[r] == true) ? *first = opt_r(*first) : NULL;
}
