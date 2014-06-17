/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_fct2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/03 19:49:45 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/06 20:29:47 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		clear_aff(void)
{
	t_hist	**historic;

	historic = init_historic(0);
	if ((*historic)->copy->size)
	{
		apply_movebegin();
		tputs(tgetstr("cd", NULL), 1, aff_c);
	}
}

void		aff_line(void)
{
	t_hist	**historic;

	historic = init_historic(0);
	if ((*historic)->copy->size)
	{
		(*historic)->copy->index = (*historic)->copy->size - 1;
		aff_str((*historic)->copy->line);
	}
}

void		apply_arrowup(void)
{
	t_hist	**historic;

	historic = init_historic(0);
	if ((*historic)->copy->up)
	{
		clear_aff();
		(*historic)->copy = (*historic)->copy->up;
		aff_line();
	}
}

void		apply_arrowdown(void)
{
	t_hist	**historic;

	historic = init_historic(0);
	if ((*historic)->copy->down)
	{
		clear_aff();
		(*historic)->copy = (*historic)->copy->down;
		aff_line();
	}
}
