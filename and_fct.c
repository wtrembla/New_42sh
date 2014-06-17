/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 18:12:26 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/13 17:23:30 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	and_proc(t_node *tree)
{
	read_tree(tree->left);
	if (g_pid.built == 1)
		read_tree(tree->right);
	else if (g_pid.father)
	{
		if (WIFEXITED(g_pid.id) && WEXITSTATUS(g_pid.id) == 0)
			read_tree(tree->right);
	}
	init_pid();
}
