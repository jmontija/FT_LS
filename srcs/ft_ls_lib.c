/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 01:31:53 by jmontija          #+#    #+#             */
/*   Updated: 2016/02/07 10:58:21 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	is_error(char *who, char *what)
{
	ft_putstr("ft_ls: ");
	ft_putstr(who);
	ft_putstr(" ");
	ft_putendl(what);
	return ;
}

void	adjust_opt(t_group *grp, char opt)
{
	opt == 'R' ? grp->options[R] = true : 0;
	opt == 't' ? grp->options[t] = true : 0;
	opt == 'r' ? grp->options[r] = true : 0;
	opt == 'l' ? grp->options[l] = true : 0;
	opt == 'a' ? grp->options[a] = true : 0;
}

int		isvalid_opt(t_group *grp, char opt)
{
	int i = -1;
	char *text;
	char *ls_options;

	adjust_opt(grp, opt);
	ls_options = SDUP("alrRt");
	text = NEW(2); text[0] = '-'; text[1] = opt; text[2] = '\0';
	while (++i < LEN(ls_options))
		if (opt == ls_options[i])
			return (1);
	is_error(text, "illegal ft_ls option or not asked\nusage: ft_ls [-alRrt] [file ...]");
	exit(0);
}

int		manage_opt(t_group *grp, char *opt)
{
	char *g_opt;
	int i;

	i = 0;
	while(++i < LEN(opt))
		if (!isvalid_opt(grp, opt[i]))
			return (false);
	return (true);
}

/*
	if -rt = -1tr
	if -rta = -1tra
	if -rtal = -1tral
	if -rtalR = -Rtral
 						*/
