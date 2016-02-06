/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 02:05:33 by jmontija          #+#    #+#             */
/*   Updated: 2016/02/06 00:43:36 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	opt_1(int maj, t_group *grp)
{
	t_dir *file;

	file = grp->first_dir;
	while (file != NULL)
	{
		if (file->name[0] != '.')
			ft_putendl(file->name);
		file = file->next;
	}
}

int	launcher(t_group *grp, char *opt)
{
	static int space = 0;

	if (grp->diropen > 0 || grp->is_R == true)
	{
		if (space != 0)
			ft_putchar('\n');
		//ft_putstr("./");
		ft_putstr(opt);
		ft_putendl(":");
		space += 1;
	}
	opt_1(1, grp);
	return (0);
}
