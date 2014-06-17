/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_fct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 17:04:06 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/13 17:17:38 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	or_proc(t_node *tree)
{
	read_tree(tree->left);
	if (WIFSIGNALED(g_pid.id) || g_pid.built == 0)
	{
		init_pid();
		read_tree(tree->right);
	}
	else if (g_pid.father != 0)
	{
		init_pid();
		if (WIFEXITED(g_pid.id) && WEXITSTATUS(g_pid.id) > 0)
			read_tree(tree->right);
	}
	init_pid();
}
