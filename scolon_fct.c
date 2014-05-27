/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scolon_fct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 14:47:28 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/18 22:08:57 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	scolon_proc(t_node *tree)
{
	read_tree(tree->left);
	read_tree(tree->right);
}
