/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 02:05:33 by jmontija          #+#    #+#             */
/*   Updated: 2016/02/06 11:31:10 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	opt_l(t_dir *file)
{
	ft_putnbr(file->slink);
	ft_putchar('\t');
	ft_putstr(file->uid);
	ft_putchar(' ');
	ft_putstr(file->gid);
	ft_putchar('\t');
	ft_putnbr(file->size);
	ft_putchar('\t');
	ft_putstr(file->last_modif);
	ft_putchar(' ');
}
void	opt_1(int maj, t_group *grp)
{
	t_dir *file;

	file = grp->first_dir;

	while (file != NULL)
	{
		if (file->name[0] != '.' || grp->options[a] == true)
		{
			if (grp->options[l] == true)
				opt_l(file);
			ft_putendl(file->name);
		}
		file = file->next;
	}
}

int	launcher(t_group *grp, char *opt)
{
	static int space = 0;

	struct stat st;

    stat(opt, &st);
    printf("size: %d\n", (int)st.st_blksize);
    printf("size: %d\n", (int)st.st_size);
    printf("size: %d\n", (int)st.st_blocks);
	if (grp->diropen > 1 || grp->options[R] == true)
	{
		if (space != 0)
			ft_putchar('\n');
		if (grp->options[R] == true && space != 0)
		{
			ft_putstr(opt);
			ft_putendl(":");
		}
		else if (grp->options[R] == false)
		{
			ft_putstr(opt);
			ft_putendl(":");
		}
		space += 1;
	}
	opt_1(1, grp);
	return (0);
}
