/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_fct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 14:56:23 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/04 19:45:10 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int				av_size(char **av)
{
	int		i;

	i = 0;
	while (av && av[i])
		i++;
	return (i);
}

void			del_av(char **av)
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

static void		launch_process(t_node **tree, t_token **toklist)
{
//	write(1, "\n", 1);
	organize_toklist(tree, toklist, 1, 0);
	print_tree(*tree, 1);
//	read_tree(*tree);
	del_tree(tree);
	init_pid();
}

void			apply_return(void)
{
	char	*trim;
	t_hist	**historic;
	t_node	*tree;
	t_token	*toklist;

	tree = NULL;
	toklist = NULL;
	historic = init_historic();
	trim = ft_strtrim((*historic)->copy->line);
	write(1, "\n", 1);
	if (trim && *trim)
	{
		(*historic)->list = add_to_list((*historic)->list,
										(*historic)->copy->line);
		create_toklist(&toklist, trim);
		if (parse_toklist(toklist))
			launch_process(&tree, &toklist);
		del_toklist(&toklist);
		del_copy(&((*historic)->copy));
		(*historic)->copy = copy_historic((*historic)->list);
	}
	else
		ft_strdel(&trim);
	display_prompt();
}
