/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historic_fct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/03 17:03:39 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/04 20:12:38 by wtrembla         ###   ########.fr       */
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
		ft_error("add_to_list: memory allocation failed");
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

t_hist			**init_historic(void)
{
	char			*line;
	char			*path;
	int				fd;
	static t_hist	*historic = NULL;

	if (!historic)
	{
		if (!(historic = (t_hist *)malloc(sizeof(t_hist))))
			ft_error("42sh: init_historic: memory allocation failed");
		path = ft_strjoin(init_env(NULL)->home, "/.42sh_history");
		if ((fd = open(path, O_RDONLY | O_CREAT, 0644)) == -1)
			ft_error("42sh: init_historic: open error: .42sh_history");
		historic->list = NULL;
		while (get_next_line(fd, &line) > 0)
		{
			historic->list = add_to_list(historic->list, line);
			ft_strdel(&line);
		}
		historic->copy = copy_historic(historic->list);
		if (close(fd) == -1)
			ft_error("42sh: init_historic: close error: .42sh_historic");
		ft_strdel(&path);
	}
	return (&historic);
}

void			del_historic(void)
{
	t_hist	**historic;

	historic = init_historic();
	del_av((*historic)->list);
	del_copy(&(*historic)->copy);
}
