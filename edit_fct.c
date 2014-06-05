/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 14:24:59 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/04 20:11:34 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char		*update_line(char *line, int index, char c)
{
	char	*update;
	int		i;
	int		j;

	i = 0;
	if (!(update = (char *)malloc(sizeof(char) * (ft_strlen(line) + 2))))
		ft_putendl_fd("42sh: update_line: memory allocation failed", 2);
	else
	{
		while (line && line[i] && i < index)
		{
			update[i] = line[i];
			i++;
		}
		update[i] = c;
		j = i;
		i++;
		while (line && line[j])
		{
			update[i] = line[j];
			i++;
			j++;
		}
		update[i] = '\0';
	}
	ft_strdel(&line);
	return (update);
}

void			apply_edit(char c)
{
	t_hist	**historic;

	historic = init_historic();
	(*historic)->copy->line = update_line((*historic)->copy->line,
											(*historic)->copy->index + 1, c);
	tputs(tgetstr("im", NULL), 1, aff_c);
	aff_c(c);
	tputs(tgetstr("ei", NULL), 1, aff_c);
	(*historic)->copy->size++;
	(*historic)->copy->index++;
	display_line();
	if (check_ending((*historic)->copy->index))
	{
		tputs(tgetstr("cr", NULL), 1, aff_c);
		tputs(tgetstr("do", NULL), 1, aff_c);
	}
}
