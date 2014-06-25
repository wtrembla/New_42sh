/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historic_fct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/03 17:03:39 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/25 18:23:09 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "ft_minishell.h"

char			**add_to_list(char **list, char *line)
{
	char	**update;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (list && list[i])
		i++;
	if (!(update = (char **)malloc(sizeof(char *) * (i + 2))))
		ft_error(ERROR(SH, E_MEMALLOC), "(creating history list)", 'y');
	while (list && list[j])
	{
		update[j] = ft_strdup(list[j]);
		j++;
	}
	update[j++] = ft_strdup(line);
	update[j] = NULL;
	del_av(list);
	return (update);
}

t_hist			**init_historic(int set)
{
	char			*line;
	char			*path;
	int				fd;
	static t_hist	*historic = NULL;

	if (!historic && set == 1)
	{
		if (!(historic = (t_hist *)malloc(sizeof(t_hist))))
			ft_error(ERROR(SH, E_MEMALLOC), "(initializing historic)", 'y');
		path = ft_strjoin(init_env(NULL, 0)->home, "/.42sh_history");
		if ((fd = open(path, O_RDONLY | O_CREAT, 0644)) == -1)
			ft_error(ERROR(SH, E_OPEN), ".42sh_history", 'y');
		historic->list = NULL;
		while (get_next_line(fd, &line) > 0)
		{
			historic->list = add_to_list(historic->list, line);
			ft_strdel(&line);
		}
		historic->copy = copy_historic(historic->list);
		if (close(fd) == -1)
			ft_error(ERROR(SH, E_CLOSE), ".42sh_history", 'n');
		ft_strdel(&path);
	}
	return (&historic);
}

void			update_historic(void)
{
	char	*path;
	int		fd;
	int		i;
	t_hist	**historic;

	i = 0;
	historic = init_historic(0);
	path = ft_strjoin(init_env(NULL, 0)->home, "/.42sh_history");
	if ((fd = open(path, O_WRONLY | O_TRUNC)) == -1)
		ft_error(ERROR(SH, E_OPEN), ".42sh_history", 'n');
	else
	{
		while ((*historic)->list && (*historic)->list[i])
		{
			ft_putendl_fd((*historic)->list[i], fd);
			i++;
		}
		if (close(fd) == -1)
			ft_error(ERROR(SH, E_CLOSE), ".42sh_history", 'n');
	}
	ft_strdel(&path);
}

void			del_historic(void)
{
	t_hist	**historic;

	historic = init_historic(0);
	if (*historic)
	{
		del_av((*historic)->list);
		del_copy(&(*historic)->copy);
	}
}
