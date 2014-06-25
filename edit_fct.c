/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/04 14:24:59 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/25 18:31:44 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char		*insert_char(char *update, char *line, int index, char c)
{
	int		i;
	int		j;

	i = 0;
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
	return (update);
}

static char		*update_line(char *line, int index, char c)
{
	char	*update;

	if (!(update = (char *)malloc(sizeof(char) * (ft_strlen(line) + 2))))
		return (update);
	else
		update = insert_char(update, line, index, c);
	ft_strdel(&line);
	return (update);
}

void			apply_edit(char c)
{
	t_hist	**historic;

	historic = init_historic(0);
	(*historic)->copy->line = update_line((*historic)->copy->line,
											(*historic)->copy->index + 1, c);
	tputs(tgetstr("im", NULL), 1, aff_c);
	aff_c(c);
	tputs(tgetstr("ei", NULL), 1, aff_c);
	(*historic)->copy->size = ft_strlen((*historic)->copy->line);
	(*historic)->copy->index = (*historic)->copy->size ?
		(*historic)->copy->index + 1 : -1;
	if (check_ending((*historic)->copy->index))
	{
		tputs(tgetstr("cr", NULL), 1, aff_c);
		tputs(tgetstr("do", NULL), 1, aff_c);
	}
	display_line();
}
