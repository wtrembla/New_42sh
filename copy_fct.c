/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/03 19:12:44 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/04 19:59:18 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_copy				*add_to_copy(t_copy *copy, char *line)
{
	t_copy  *elem;
	t_copy  *tmp;

	tmp = copy;
	if (!(elem = (t_copy *)malloc(sizeof(t_copy))))
		ft_error("42sh: add_to_copy: memory allocation failed");
	elem->line = ft_strdup(line);
	elem->size = ft_strlen(line);
	elem->index = line ? elem->size - 1 : - 1;
	elem->up = NULL;
	elem->down = NULL;
	if (copy)
	{
		while (tmp->down)
			tmp  = tmp->down;
		tmp->down = elem;
		tmp->down->up = tmp;
	}
	else
		copy = elem;
	return (copy);
}

t_copy              *copy_historic(char **list)
{
	int         i;
	t_copy      *copy;

	i = 0;
	copy = NULL;
	while (list && list[i])
	{
		copy = add_to_copy(copy, list[i]);
		i++;
	}
	copy = add_to_copy(copy, NULL);
	while (copy->down)
		copy = copy->down;
	return (copy);
}

void				del_copy(t_copy **copy)
{
	t_copy  *tmp;

	while ((*copy)->up)
		*copy = (*copy)->up;
	while (*copy)
	{
		tmp = *copy;
		*copy = (*copy)->down;
		ft_strdel(&tmp->line);
		tmp->up = NULL;
		tmp->down = NULL;
		free(tmp);
		tmp = NULL;
	}
}
