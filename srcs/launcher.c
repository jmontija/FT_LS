/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 02:05:33 by jmontija          #+#    #+#             */
/*   Updated: 2016/02/07 11:23:11 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_nblen(int nb)
{
	int i;

	i = 1;
	while (nb /= 10)
		i++;
	return (i);
}

void	len_space_link(t_group *grp)
{
	t_dir *test;
	int i = 0;

	test = grp->first_dir;
	while (test != NULL)
	{
		i = ft_nblen(test->slink);
		if (i > grp->link_space)
			grp->link_space = i;
		test = test->next;
	}
	//printf("link_max %d\n", grp->link_space);
}

void	len_space_size(t_group *grp)
{
	t_dir *test;
	int i = 0;

	test = grp->first_dir;
	while (test != NULL)
	{
		i = ft_nblen(test->size);
		if (i > grp->size_space)
			grp->size_space = i;
		test = test->next;
	}
	//printf("size_max %d\n", grp->size_space);
}

void	opt_l(t_group *grp, t_dir *file)
{
	int link_space_max = grp->link_space;
	int size_space_max = grp->size_space;
	int len_file_link  = ft_nblen(file->slink);
	int len_file_size  = ft_nblen(file->size);

	ft_putstr(file->rights);
	ft_putstr("  ");
	while (len_file_link++ < link_space_max)
		ft_putchar(' ');
	ft_putnbr(file->slink);
	ft_putchar(' ');
	ft_putstr(file->uid);
	ft_putstr("  ");
	ft_putstr(file->gid);
	while (len_file_size++ < size_space_max)
		ft_putchar(' ');
	ft_putstr("  ");
	ft_putnbr(file->size);
	/* attention un espace au debut du last_modif dû au strchr qui renvois la chaine a l'espace avec l'espace*/
	ft_putstr(file->last_modif);
	ft_putchar(' ');
}

void	opt_1(t_group *grp)
{
	t_dir *file;

	file = grp->first_dir;

	while (file != NULL)
	{
		if (file->name[0] != '.' || grp->options[a] == true)
		{
			if (grp->options[l] == true)
				opt_l(grp, file);
			ft_putendl(file->name);
		}
		file = file->next;
	}
}

int	launcher(t_group *grp, char *opt)
{
	static int space = 0;

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
	len_space_link(grp);
	len_space_size(grp);
	opt_1(grp);
	return (0);
}
