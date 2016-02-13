/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 02:05:33 by jmontija          #+#    #+#             */
/*   Updated: 2016/02/09 06:01:02 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void show_total_blocks(t_group *grp, t_dir *file)
{
	int total = 0;
	while (file != NULL)
	{
		if (file->name[0] != '.' || grp->options[a] == true)
			total += file->blocks;
		if (file->isopt == 2)
			total = -1;
		file = file->next;
	}
	if ((total == 0 && grp->options[a] == false) || total == -1)
		return ;
	ft_putstr("total ");
	ft_putnbr(total);
	ft_putchar('\n');
}

int		display_files(t_group *grp, char *opt)
{
	t_dir 	*file;
	int 	ret;

	ret = 0;
	file = grp->first_dir;
	if (grp->options[l] == true && opt != NULL)
		show_total_blocks(grp, file);
	while (file != NULL)
	{
		if (file->name[0] != '.' || grp->options[a] == true)
		{
			if (grp->options[l] == true && file->isopt != 2)
				opt_l(grp, file);
			else if (file->isopt == 2)
			{
				ft_putstr("permission denied -> ");
				ret = -1;
			}
			ft_putendl(file->name);
		}
		file = file->next;
	}
	return (ret);
}

int	launcher(t_group *grp, char *opt)
{
	static int space = 0;

	if (grp->diropen > 1  && opt != NULL)
	{
		if (space != 0)
			ft_putchar('\n');
		ft_putstr(opt);
		ft_putendl(":");
		space += 1;
	}
	else if (grp->options[R] == true)
		space += 1;
	if (display_files(grp, opt) == -1)
	{
		ft_putstr("permission denied -> ");
		ft_putendl(strrchr(opt, '/') + 1);
	}
	return (0);
}
