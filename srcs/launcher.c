/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 02:05:33 by jmontija          #+#    #+#             */
/*   Updated: 2016/02/08 17:10:44 by jmontija         ###   ########.fr       */
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
	ft_putchar('\t');
	ft_putstr(file->gid);
	ft_putchar('\t');
	/*while (len_file_size++ < size_space_max)
		ft_putchar(' ');
	ft_putstr("  ");*/
	ft_putnbr(file->size);
	/* attention un espace au debut du last_modif dû au strchr qui renvois la chaine a l'espace avec l'espace */
	ft_putstr(file->last_modif);
	ft_putchar(' ');
}

void show_total_blocks(t_group *grp, t_dir *file)
{
	int total = 0;
	while (file != NULL)
	{
		if (file->name[0] != '.' || grp->options[a] == true)
			total += file->blocks;
		if (file->isopt == 2)
			total = -1;
		//printf("%s: %d\n", file->name, file->blocks);
		file = file->next;
	}
	if ((total == 0 && grp->options[a] == false) || total == -1)
		return ;
	ft_putstr("total ");
	ft_putnbr(total);
	ft_putchar('\n');
}

int		opt_1(t_group *grp, char *opt)
{
	t_dir *file;
	int ret = 0;
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

/*
struct stat		buf;
stat("~/ft_ls", &buf);
printf("BLOCKS %lld\n", buf.st_blocks);
*/

if ((grp->diropen > 1 || grp->options[R] == true) && opt != NULL)
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
if (opt_1(grp, opt) == -1)
{
	ft_putstr("permission denied -> ");
	ft_putendl(strrchr(opt, '/') + 1);
}
return (0);
}
