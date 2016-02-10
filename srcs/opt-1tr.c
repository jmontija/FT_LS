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

void	opt_OE(t_dir	*new, t_dir **first, t_dir **curr)
{
	t_dir	*last_other;
	t_dir	*other;

	if (*curr != NULL)
	{
		other = *first;
		if (strcmp(new->name, other->name) < 0)
		{
			//printf("%s becomes *first element\n", new->name);
			*first = new;
			new->next = other;
			return ;
		}
		while (other != NULL)
		{
			if (strcmp(new->name, other->name) < 0)
			{
				//printf("insert %s between %s & %s\n", new->name, last_other->name, other->name);
				last_other->next = new;
				new->next = other;
				return ;
			}
			last_other = other;
			other = other->next;
		}
		(*curr)->next = new;
		//printf("%s becomes last element\n", new->name);
	}
	else
	{
		//printf("entrance: %s becomes *first element\n", new->name);
		 *first = new;
	}
	*curr = new;
}

void	opt_t(t_dir	*new, t_dir **first, t_dir **curr)
{

}

/*void reverse(struct node** head_ref)
{
    struct node* prev   = NULL;
    struct node* current = *head_ref;
    struct node* next;
    while (current != NULL)
    {
        next  = current->next;  
        current->next = prev;   
        prev = current;
        current = next;
    }
    *head_ref = prev;
}*/

void	opt_r(t_dir	*new, t_dir **first, t_dir **curr)
{

}

int	 sort_launcher(t_group *grp, t_dir *new, t_dir **first, t_dir **curr)
{
	if (grp->options[t] || grp->options[r])
	{
		//grp->options[t] = true ? opt_t(new, first, curr) : NULL;
		//grp->options[r] = true ? opt_r(new, first, curr) : NULL;
	}
	else
		opt_OE(new, first, curr);
	return (1);
}