/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_fct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/15 19:08:45 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/16 15:25:48 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static t_proc	init_process(char *operand, void *apply_proc)
{
	t_proc	process;

	process.operand = ft_strdup(operand);
	process.apply_proc = apply_proc;
	return (process);
}

t_proc			*init_proctab(void)
{
	static t_proc	*proc_tab = NULL;

	if (!proc_tab)
	{
		if (!(proc_tab = (t_proc *)malloc(sizeof(t_proc) * OPE_NUM)))
			ft_error("init_proctab: memory allcoation failed");
		proc_tab[0] = init_process(";", &scolon_proc);
		proc_tab[1] = init_process("|", &pipe_proc);
		proc_tab[2] = init_process(">>", &redirr_proc);
		proc_tab[3] = init_process(">", &redir_proc);
		proc_tab[4] = init_process("<", &redil_proc);
	}
	return (proc_tab);
}

void			del_proctab(void)
{
	int		i;
	t_proc	*proc_tab;

	i = 0;
	proc_tab = init_proctab();
	if (proc_tab)
	{
		while (i < OPE_NUM)
		{
			ft_strdel(&proc_tab[i].operand);
			proc_tab[i].operand = NULL;
			i++;
		}
	}
}

void			read_tree(t_node *tree)
{
	int		i;
	t_proc	*proc_tab;

	i = 0;
	proc_tab = init_proctab();
	while (i < OPE_NUM)
	{
		if (!ft_strcmp(tree->type, proc_tab[i].operand))
		{
			proc_tab[i].apply_proc(tree);
			break ;
		}
		i++;
	}
	if (!ft_strcmp(tree->type, "com"))
	{
		if (!check_builtin(tree->word))
			command_proc(tree->word);
	}
}
