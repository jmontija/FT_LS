/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 23:36:54 by julio             #+#    #+#             */
/*   Updated: 2016/02/05 02:18:26 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		manage_opt(t_group *grp, char *opt)
{
	char *g_opt;
	int i;

	i = 0;
	if (grp->options == NULL)
		grp->options = SDUP("");
	g_opt = grp->options;
	while(++i < LEN(opt))
		if (!isvalid_opt(grp, opt[i]))
			return (false);
	char *letters = SUB(opt, 1, LEN(opt));
	grp->options = JOIN(grp->options, letters);
	REMOVE(&letters);
	REMOVE(&g_opt);
	return (true);
}

int		manage_dir(int launch, t_group *grp, int argc, char **argv)
{
	DIR				*directory;
	struct dirent	*file;
	char 			**sub_dir = NULL;
	unsigned char isDIR = 4;
	int i = 0;
	int j = 0;
	int open = 0;
	char *joe;
	int static diremp = 0;

	if (launch == 0) i = 0; else i = -1;
	if (sub_dir == NULL)
		sub_dir = (char **)malloc(sizeof(char *) * 100);
	while (++i < argc)
	{
		//printf("KD%s\n", argv[i]);
		if (*argv[i] == '-' && grp->diropen == 0 && manage_opt(grp, argv[i]) == true)
		{}
		else
		{
			//printf("checking: %s\n", argv[i]);
			if (!(directory = opendir(argv[i])))
				is_error(argv[i], "is not an available directory");
			else
			{
				organize_dir(launch, grp, argv[i]);
				while (grp->is_R && (file = readdir(directory)))
				{
					if (file->d_type == isDIR && file->d_name[0] != '.')
					{
						//printf("dir found %s\n", file->d_name);
						joe = JOIN(argv[i], "/");
						sub_dir[j] = JOIN(joe, file->d_name);
						REMOVE(&joe);
						//printf("sub_dir_organize %s\n", sub_dir[j]);
						j++;
					}
					//else
						//printf("one file found\n");
				}
				//printf("sub_dir = %d\n", j);
				closedir(directory);
				open++;
				if (j > 0)
				{
					diremp++;
					manage_dir(diremp, grp, j, sub_dir);
					diremp = 0;
					j = 0;
				}
			}
			grp->diropen += 1;
		}
	}
	//organize_opt(grp->options);
	return ((open > 0) ? 1 : 0);
}

int		main(int argc, char **argv)
{
	t_group *grp;
	char *root;
	int	i = 0;
	int dir_open;

	grp = init_grp();
	root = SDUP(".");
	if (manage_dir(0, grp, argc, argv))
	{
		printf("Let's open directories, options set: -%s\n", grp->options);
		prelauncher(grp);
	}
	else if (grp->diropen == false)
	{
		//printf("Let's open root, options set: -%s\n", grp->options);
		organize_dir(0, grp, root);
		prelauncher(grp);
	}
	else
		is_error("stop", "");
	//printf("dirOpen: %d\n", grp->diropen);
	return (0);
}
