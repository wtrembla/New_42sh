/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_fct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 14:56:23 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/25 16:57:56 by wtrembla         ###   ########.fr       */
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
	organize_toklist(tree, toklist, 1, 0);
//	print_tree(*tree, 1);
	apply_term(-1);
	read_tree(*tree);
	apply_term(1);
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
	historic = init_historic(0);
	trim = ft_strtrim((*historic)->copy->line);
	if (trim && *trim)
	{
		(*historic)->list = add_to_list((*historic)->list,
										(*historic)->copy->line);
		create_toklist(&toklist, trim);
		if (!parse_toklist(toklist))
			launch_process(&tree, &toklist);
		del_toklist(&toklist);
		del_copy(&((*historic)->copy));
		(*historic)->copy = copy_historic((*historic)->list);
	}
	else
		ft_strdel(&trim);
}
