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

void	show_total_blocks(t_group *grp, t_dir *file)
{
	int	total;
	int	count;

	total = 0;
	count = 0;
	while (file != NULL)
	{
		if ((file->name[0] != '.' || grp->options[a] == true ||
			grp->options[f] == true) && file->isopt != 2)
			total += file->blocks;
		count++;
		file = file->next;
	}
	if (total == 0 && count == 2 &&
		grp->options[a] == false && grp->options[f] == false)
		return ;
	ft_putstr("total ");
	ft_putnbr(total);
	ft_putchar('\n');
}

void	display_errors(t_dir *file)
{
	while (file != NULL)
	{
		if (file->isopt == 2)
			perror(ft_strjoin("ft_ls: ", file->name));
		file = file->next;
	}
}

int		display_files(t_group *grp, char *opt)
{
	t_dir	*file;
	int		ret;

	ret = 0;
	file = grp->first_dir;
	display_errors(file);
	if ((grp->options[l] == true || grp->options[g] == true) && opt != NULL)
		show_total_blocks(grp, file);
	while (file != NULL)
	{
		if (file->name[0] != '.' || grp->options[a] == true ||
			grp->options[f] == true || grp->options[d] == true)
		{
			if ((grp->options[l] == true ||
				grp->options[g] == true) && file->isopt != 2)
				opt_l(grp, file);
			if (file->isopt != 2)
				ft_putendl(file->name);
		}
		file = file->next;
	}
	return (ret);
}

int		launcher(t_group *grp, char *opt)
{
	static int space = 0;

	if (grp->diropen > 1 && opt != NULL)
	{
		if (space != 0)
			ft_putchar('\n');
		ft_putstr(opt);
		ft_putendl(":");
		space += 1;
	}
	else if (grp->options[R] == true)
		space += 1;
	display_files(grp, opt);
	return (0);
}
