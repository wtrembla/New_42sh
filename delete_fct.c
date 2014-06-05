/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_fct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/03 20:00:33 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/04 20:11:15 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void			display_line(void)
{
	t_hist	**historic;

	historic = init_historic();
	tputs(tgetstr("cd", NULL), 1, aff_c);
    tputs(tgetstr("sc", NULL), 1, aff_c);
    aff_str((*historic)->copy->line + (*historic)->copy->index + 1);
    tputs(tgetstr("rc", NULL), 1, aff_c);
}

static char		*update_line(char *line, int index)
{
	char 	*update;
	int		i;
	int		j;

	i = 0;
	if (!(update = (char *)malloc(sizeof(char) * ft_strlen(line))))
		ft_putendl_fd("42sh: update_line: memory allocation failed", 2);
	else
	{
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
	}
	ft_strdel(&line);
	return (update);
}

void			apply_delete(void)
{
	int		win_size;
	t_hist	**historic;

	historic = init_historic();
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
		(*historic)->copy->size -= 1;
		display_line();
	}
}