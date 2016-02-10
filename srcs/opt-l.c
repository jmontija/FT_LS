/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt-l.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 01:00:29 by julio             #+#    #+#             */
/*   Updated: 2016/02/09 03:23:39 by julio            ###   ########.fr       */
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

void	opt_l(t_group *grp, t_dir *file)
{
	t_space	*s_grp = NULL;
	int len_file_uid     = LEN(file->uid);
	int len_file_grpid   = LEN(file->gid);
	int len_file_link    = ft_nblen(file->slink);
	int len_file_size    = ft_nblen(file->size);

	s_grp = define_space(grp, file);
	ft_putstr(file->rights);
	ft_putstr("  ");
	while (len_file_link++ < s_grp->link_space)
		ft_putchar(' ');
	ft_putnbr(file->slink);
	ft_putchar(' ');
	ft_putstr(file->uid);
	while (len_file_uid++ < s_grp->uid_space + 2)
		ft_putchar(' ');
	ft_putstr(file->gid);
	while (len_file_grpid++ < s_grp->grpid_space + 2)
		ft_putchar(' ');
	while (len_file_size++ < s_grp->size_space)
		ft_putchar(' ');
	ft_putnbr(file->size);
	if (file->size_min >= 0)
	{
		ft_putchar(',');
		ft_putstr("  ");
		ft_putnbr(file->size_min);
		ft_putchar('\t');
	}
	/* attention un espace au debut du last_modif dû au strchr qui renvois la chaine a l'espace avec l'espace */
	ft_putstr(file->last_modif);
	ft_putchar(' ');
	ft_memdel((void*)&s_grp);
}