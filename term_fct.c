/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 15:15:43 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/11 19:38:16 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	apply_term(int set)
{
	struct termios	term;

	if (set == 1)
	{
		tcgetattr(0, &term);
		term.c_lflag &= ~(ICANON | ECHO);
		term.c_cc[VMIN] = 1;
		term.c_cc[VTIME] = 0;
		tcsetattr(0, 0, &term);
	}
	else if (set == -1)
	{
		tcgetattr(0, &term);
		term.c_lflag |= (ICANON | ECHO);
		tcsetattr(0, 0, &term);
	}
}
