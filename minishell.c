/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 14:56:23 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/22 18:42:12 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		av_size(char **av)
{
	int		i;

	i = 0;
	while (av && av[i])
		i++;
	return (i);
}

void	del_av(char **av)
{
	int		i;

	i = 0;
	if (av)
	{
		while (av[i])
		{
			ft_strdel(&av[i]);
			i++;
		}
		free(av);
		av = NULL;
	}
}

void	minishell(void)
{
	char	*line;
	char	*trim;
	t_node	*tree;
	t_token	*toklist;

	tree = NULL;
	toklist = NULL;
	catch_signal();
	while (get_next_line(0, &line))
	{
		init_pid();
		trim = ft_strtrim(line);
		if (trim && *trim)
		{
			create_toklist(&toklist, trim);
			if (parse_toklist(toklist))
			{
				organize_toklist(&tree, &toklist, 1, 0);
//				print_tree(tree, 1);
				read_tree(tree);
				del_tree(&tree);
			}
			del_toklist(&toklist);
		}
		else
			ft_strdel(&trim);
		ft_strdel(&line);
		display_prompt();
	}
	apply_exit(NULL);
}
