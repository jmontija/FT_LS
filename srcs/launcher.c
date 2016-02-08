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
	if (nb > 0)
	{
		while (nb /= 10)
			i++;
	}
	return (i);
}

void	len_space_slink(t_group *grp, t_space *s_grp)
{
	t_dir *test;
	int i = 0;

	s_grp->link_space = 0;
	test = grp->first_dir;
	while (test != NULL)
	{
		if (test->slink)
		{
			i = ft_nblen(test->slink);
			if (i > s_grp->link_space)
				s_grp->link_space = i;
		}
			test = test->next;
	}
	printf("link_max %d\n", s_grp->link_space);
}

void	len_space_size(t_group *grp, t_space *s_grp)
{
	t_dir *test;
	int i = 0;

	s_grp->size_space = 0;
	test = grp->first_dir;
	while (test != NULL)
	{
		if (test->size)
		{
			i = ft_nblen(test->size);
			if (i > s_grp->size_space)
				s_grp->size_space = i;
		}
		test = test->next;
	}
	printf("size_max %d\n", s_grp->size_space);
}

void	len_space_uid(t_group *grp, t_space *s_grp)
{
	t_dir *test;
	int i = 0;

	s_grp->uid_space = 0;
	test = grp->first_dir;
	while (test != NULL)
	{
		if (test->uid)
		{
			i = (int)LEN(test->uid);
			if (i > s_grp->uid_space)
				s_grp->uid_space = i;
		}
		test = test->next;
	}
	printf("uid_max %d\n", s_grp->uid_space);
}

void	len_space_grpid(t_group *grp, t_space *s_grp)
{
	t_dir *test;
	int i = 0;

	s_grp->grpid_space = 0;
	test = grp->first_dir;
	while (test != NULL)
	{
		if (test->gid)
		{
			i = (int)LEN(test->gid);
			if (i > s_grp->grpid_space)
				s_grp->grpid_space = i;
		}
		test = test->next;
	}
	printf("grpid_max %d\n", s_grp->grpid_space);
}

void	opt_l(t_space *s_grp, t_dir *file)
{
	//faire une fonciton pour toute cette merde  !!!!!
	/*int link_space_max = s_grp->link_space;
	int size_space_max = s_grp->size_space;
	int uid_space_max  = s_grp->uid_space;
	int gid_space_max  = s_grp->grpid_space;*/

	/*int len_file_uid     = LEN(file->uid);
	int len_file_grpid   = LEN(file->gid);
	int len_file_link    = ft_nblen(file->slink);
	int len_file_size    = ft_nblen(file->size);*/

	ft_putstr(file->rights);
	ft_putstr("  ");
	//while (len_file_link++ < link_space_max)
		ft_putchar(' ');
	ft_putnbr(file->slink);
	ft_putchar(' ');
	ft_putstr(file->uid);
	//while (len_file_uid++ < uid_space_max + 2)
		ft_putchar(' ');
	ft_putstr(file->gid);
	//while (len_file_grpid++ < gid_space_max + 2)
		ft_putchar(' ');
	//while (len_file_size++ < size_space_max)
		ft_putchar(' ');
	ft_putnbr(file->size);
	/* attention un espace au debut du last_modif dû au strchr qui renvois la chaine a l'espace avec l'espace */
	ft_putstr(file->last_modif);
	ft_putchar('\t');
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
	t_dir 	*file;
	t_space	*s_grp;
	int 	ret;

	ret = 0;
	file = grp->first_dir;
	if (grp->options[l] == true && opt != NULL)
	{
		/*if (s_grp == NULL)
			s_grp = (t_space*)malloc(sizeof(t_space));
		len_space_slink(grp, s_grp);
		len_space_size(grp, s_grp);
		len_space_uid(grp, s_grp);
		len_space_grpid(grp, s_grp);*/
		show_total_blocks(grp, file);
	}
	while (file != NULL)
	{
		if (file->name[0] != '.' || grp->options[a] == true)
		{
			if (grp->options[l] == true && file->isopt != 2)
				opt_l(s_grp, file);
			else if (file->isopt == 2)
			{
				ft_putstr("permission denied -> ");
				ret = -1;
			}
			ft_putendl(file->name);
		}
		file = file->next;
	}
	printf("retOUT: %d\n", ret);
	return (ret);
}

int	launcher(t_group *grp, char *opt)
{
	static int space = 0;

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
	/*if (opt_1(grp, opt) == -1)
	{	
		ft_putstr("permission denied -> ");
		ft_putendl(strrchr(opt, '/') + 1);
	}*/
	t_space	*s_grp;

	if (grp->options[l] == true && opt != NULL)
	{
		if (s_grp == NULL)
			s_grp = (t_space*)malloc(sizeof(t_space));
		len_space_slink(grp, s_grp);
		len_space_size(grp, s_grp);
		//len_space_uid(grp, s_grp);
		//len_space_grpid(grp, s_grp);
	}
	opt_1(grp, opt);
	printf("OUTLAUNCHER\n");
	return (0);
}
