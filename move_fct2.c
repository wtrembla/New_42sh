/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_fct2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/05 19:10:56 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/11 19:36:35 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void		cursor_down(int move, int index)
{
	int		i;

	i = index;
	while (i < move)
	{
		if (check_ending(i))
			tputs(tgetstr("do", NULL), 1, aff_c);
		tputs(tgetstr("nd", NULL), 0, aff_c);
		i++;
	}
}

void			apply_moveup(void)
{
	struct winsize	size;
	t_hist			**historic;

	historic = init_historic(0);
	ioctl(0, TIOCGWINSZ, &size);
	if ((*historic)->copy->index - size.ws_col >= -1)
	{
		tputs(tgetstr("up", NULL), 0, aff_c);
		(*historic)->copy->index -= size.ws_col;
	}
	else if ((*historic)->copy->index - size.ws_col >= -3)
	{
		tputs(tgetstr("up", NULL), 0, aff_c);
		tputs(tgoto(tgetstr("ch", NULL), 0, 2), 1, aff_c);
		(*historic)->copy->index = -1;
	}
}

void			apply_movedown(void)
{
	struct winsize	size;
	t_hist			**historic;

	historic = init_historic(0);
	ioctl(0, TIOCGWINSZ, &size);
	if ((*historic)->copy->index + size.ws_col < (*historic)->copy->size)
	{
		cursor_down((*historic)->copy->index + size.ws_col,
					(*historic)->copy->index);
		(*historic)->copy->index += size.ws_col;
	}
	else
	{
		cursor_down((*historic)->copy->size - 1, (*historic)->copy->index);
		(*historic)->copy->index = (*historic)->copy->size - 1;
	}
}
