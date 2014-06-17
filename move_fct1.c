/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_fct1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 20:06:58 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/11 19:36:09 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void		cursor_left(int move, int index)
{
	int				i;
	struct winsize	size;

	i = 0;
	while (i < move)
	{
		if (check_beginning(index - i - 1))
		{
			tputs(tgetstr("up", NULL), 1, aff_c);
			tputs(tgoto(tgetstr("ch", NULL), 0, size.ws_col), 1, aff_c);
		}
		else
			tputs(tgetstr("le", NULL), 1, aff_c);
		i++;
	}
}

static void		cursor_right(int move, int index)
{
	int		i;

	i = 0;
	while (i < move)
	{
		if (check_ending(index + i))
			tputs(tgetstr("do", NULL), 1, aff_c);
		tputs(tgetstr("nd", NULL), 1, aff_c);
		i++;
	}
}

void			apply_moveleft(void)
{
	char	*line;
	int		i;
	int		index;
	t_hist	**historic;

	i = 0;
	historic = init_historic(0);
	index = (*historic)->copy->index;
	line = (*historic)->copy->line;
	while (line && line[index - i] && index - i > -1
			&& (line[index - i] == ' ' || line[index - i] == '\t'))
		i++;
	while (line && line[index - i] && index - i > -1
			&& line[index - i] != ' ' && line[index - i] != '\t')
		i++;
	if (line && (line[index - i] || index - i == -1))
	{
		cursor_left(i, index);
		(*historic)->copy->index -= i;
	}
}

void			apply_moveright(void)
{
	char	*line;
	int		i;
	int		index;
	t_hist	**historic;

	i = 1;
	historic = init_historic(0);
	index = (*historic)->copy->index;
	line = (*historic)->copy->line;
	while (line && line[index + i]
			&& line[index + i] != ' ' && line[index + i] != '\t')
		i++;
	while (line && line[index + i]
			&& (line[index + i] == ' ' || line[index + i] == '\t'))
		i++;
	if (line && line[index + i])
	{
		cursor_right(i - 1, index);
		(*historic)->copy->index += i - 1;
	}
}
