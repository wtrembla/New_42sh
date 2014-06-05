/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_fct1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/03 19:35:50 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/04 16:35:59 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		check_ending(int index)
{
	struct winsize  size;

	ioctl(0, TIOCGWINSZ, &size);
	if (((index + 3) % (size.ws_col)) == 0)
		return (1);
	else
		return (0);
}

int		check_beginning(int index)
{
	struct winsize  size;

	ioctl(0, TIOCGWINSZ, &size);
	if ((index + 3 % size.ws_col) == size.ws_col - 1)
		return (size.ws_col);
	else
		return (0);
}

void	apply_arrowright(void)
{
	t_hist	**historic;

	historic = init_historic();
	if ((*historic)->copy->index < (*historic)->copy->size - 1)
	{
		(*historic)->copy->index += 1;
		tputs(tgetstr("nd", NULL), 1, aff_c);
		if (check_ending((*historic)->copy->index))
		{
			tputs(tgetstr("cr", NULL), 1, aff_c);
			tputs(tgetstr("do", NULL), 1, aff_c);
		}
	}
}

void	apply_arrowleft(void)
{
	int		win_size;
	t_hist	**historic;

	historic = init_historic();
	if ((*historic)->copy->index > -1)
	{
		(*historic)->copy->index -= 1;
		if ((win_size = check_beginning((*historic)->copy->index)))
		{
			tputs(tgetstr("up", NULL), 1, aff_c);
			tputs(tgoto(tgetstr("ch", NULL), 0, win_size), 1, aff_c);
		}
		else
			tputs(tgetstr("le", NULL), 1, aff_c);
	}
}
