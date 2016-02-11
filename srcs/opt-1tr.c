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

void	opt_t2(t_dir *new, t_dir **first, t_dir **curr)
{
	t_dir	*last_other;
	t_dir	*other;

	if (*curr != NULL)
	{
		other = *first;
		if (strncmp(new->last_modif, other->last_modif, 5) < 0)
		{
			*first = new;
			new->next = other;
			return ;
		}
		while (other != NULL)
		{
			if (strncmp(new->last_modif, other->last_modif, 5) < 0)
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

void	opt_t(t_dir **first)
{
	t_dir	*other = *first;
	t_dir	*curr = NULL;
	t_dir 	*wtf = NULL;

	while (other != NULL)
	{
		
		if (other->last_modif)
		{
			//printf("%s %s\n", other->name, other->last_modif);
			opt_t2(other, first, &curr);
		}
		other = other->next;
	}
	//*first = wtf;
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