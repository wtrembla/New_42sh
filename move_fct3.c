/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_fct3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 17:06:34 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/06 20:30:58 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	apply_moveend(void)
{
	clear_aff();
	aff_line();
}

void	apply_movebegin(void)
{
	struct winsize	size;
	t_hist			**historic;

	ioctl(0, TIOCGWINSZ, &size);
	historic = init_historic(0);
	while ((*historic)->copy->index + 3 >= size.ws_col)
		apply_moveup();
	if ((*historic)->copy->index != -1)
	{
		tputs(tgoto(tgetstr("ch", NULL), 0, 2), 1, aff_c);
		(*historic)->copy->index = -1;
	}
}
