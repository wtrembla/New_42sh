/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_fct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/03 20:00:33 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/25 18:11:38 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char		*delete_char(char *update, char *line, int index)
{
	int		i;
	int		j;

	i = 0;
	while (line && line[i] && i < index)
	{
		update[i] = line[i];
		i++;
	}
	j = i;
	i++;
	while (line && line[i])
	{
		update[j] = line[i];
		i++;
		j++;
	}
	update[j] = '\0';
	return (update);
}

void			display_line(void)
{
	t_hist	**historic;

	historic = init_historic(0);
	tputs(tgetstr("cd", NULL), 1, aff_c);
	tputs(tgetstr("sc", NULL), 1, aff_c);
	aff_str((*historic)->copy->line + (*historic)->copy->index + 1);
	tputs(tgetstr("rc", NULL), 1, aff_c);
}

static char		*update_line(char *line, int index)
{
	char	*update;

	if (!(update = (char *)malloc(sizeof(char) * ft_strlen(line))))
		return (update);
	else
		update = delete_char(update, line, index);
	ft_strdel(&line);
	return (update);
}

void			apply_delete(void)
{
	int		win_size;
	t_hist	**historic;

	historic = init_historic(0);
	if ((*historic)->copy->index != -1)
	{
		(*historic)->copy->line = update_line((*historic)->copy->line,
												(*historic)->copy->index);
		if ((win_size = check_beginning((*historic)->copy->index)))
		{
			tputs(tgetstr("up", NULL), 1, aff_c);
			tputs(tgoto(tgetstr("ch", NULL), 0, win_size), 1, aff_c);
		}
		else
			tputs(tgetstr("le", NULL), 1, aff_c);
		tputs(tgetstr("dc", NULL), 1, aff_c);
		(*historic)->copy->index -= 1;
		(*historic)->copy->size = ft_strlen((*historic)->copy->line);
		display_line();
	}
}
