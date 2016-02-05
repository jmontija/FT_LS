/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 01:31:53 by jmontija          #+#    #+#             */
/*   Updated: 2016/02/04 21:29:08 by jmontija         ###   ########.fr       */
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

void	organize_opt(char *options)
{
	printf("options_set = -%s\n", options);
}

int		isvalid_opt(t_group *grp, char opt)
{
	int i = -1;
	char *text;

	char *ls_options = SDUP("alrRt");
	text = NEW(2); text[0] = '-'; text[1] = opt; text[2] = '\0';
	if (opt == 'R')
		grp->is_R = true;
	while (++i < LEN(ls_options))
		if (opt == ls_options[i])
			return (1);
	is_error(text, "illegal ft_ls option or not asked\nusage: ft_ls [-alRrt] [file ...]");
	exit(0);
}

/*
	if -rt = -1tr
	if -rta = -1tra
	if -rtal = -1tral
	if -rtalR = -Rtral
 						*/
