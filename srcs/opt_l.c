/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_l.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 01:00:29 by julio             #+#    #+#             */
/*   Updated: 2016/03/02 19:28:41 by jmontija         ###   ########.fr       */
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

t_space	*define_space(t_group *grp)
{
	t_space *s_grp;

	s_grp = (t_space*)malloc(sizeof(t_space));
	len_space_slink(grp, s_grp);
	len_space_size(grp, s_grp);
	len_space_size_min(grp, s_grp);
	len_space_uid(grp, s_grp);
	len_space_grpid(grp, s_grp);
	return (s_grp);
}

void	opt_l_next(t_group *grp, t_space *s_grp, t_dir *file)
{
	int len_file_size;
	int len_file_size_min;

	len_file_size = ft_nblen(file->size);
	len_file_size_min = ft_nblen(file->size_min);
	while (len_file_size++ < s_grp->size_space)
		ft_putchar(' ');
	len_file_size = ft_nblen(file->size);
	(grp->ismaj_min == false) ? ft_putstr("  ") : ft_putchar(' ');
	if (file->size_min < 0 && grp->ismaj_min)
		while (len_file_size++ < s_grp->size_space + 2)
			ft_putchar(' ');
	ft_putnbr(file->size);
	if (file->size_min >= 0)
	{
		ft_putchar(',');
		while (len_file_size_min++ < s_grp->size_min_space + 1)
			ft_putchar(' ');
		ft_putnbr(file->size_min);
	}
	ft_putstr(file->last_modif);
	ft_putchar(' ');
}

void	opt_l(t_group *grp, t_dir *file)
{
	t_space	*s_grp;
	int		len_file_link;
	int		len_file_uid;
	int		len_file_grpid;

	s_grp = define_space(grp);
	len_file_link = ft_nblen(file->slink);
	len_file_uid = LEN(file->uid);
	len_file_grpid = LEN(file->gid);
	ft_putstr(file->rights);
	while (len_file_link++ < s_grp->link_space + 1)
		ft_putchar(' ');
	ft_putnbr(file->slink);
	ft_putchar(' ');
	if (grp->options[g] == false)
	{
		ft_putstr(file->uid);
		while (len_file_uid++ < s_grp->uid_space + 2)
			ft_putchar(' ');
	}
	ft_putstr(file->gid);
	while (len_file_grpid++ < s_grp->grpid_space)
		ft_putchar(' ');
	opt_l_next(grp, s_grp, file);
	ft_memdel((void*)&s_grp);
}
