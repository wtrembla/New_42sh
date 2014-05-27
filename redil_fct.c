/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redil_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 14:50:09 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/27 15:58:53 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "ft_minishell.h"

static int		check_file(char *file)
{
	int		fd;

	fd = -1;
	if (!access(file, F_OK) && access(file, W_OK) == -1)
		ft_putjoin_fd("42sh: permission denied: ", file, 2);
	else if ((fd = open(file, O_RDONLY)) == -1)
		ft_putjoin_fd("42sh: check_file: open error: ", file, 2);
	return (fd);
}

void		write_redilfile(void)
{
	char	*line;
	t_data	*data;
	t_fd	*tmp;

	data = init_data();
	tmp = data->infildes;
	while (tmp)
	{
		while (get_next_line(tmp->fildes, &line) > 0)
		{
			ft_putendl_fd(line, data->tmp_fdin);
			ft_strdel(&line);
		}
		tmp = tmp->next;
	}
	lseek(data->tmp_fdin, 0, SEEK_SET);
}

void			add_infildes(t_fd **infildes, char *file, int fd)
{
	t_fd	*elem;
	t_fd	*tmp;

	if (!(elem = (t_fd *)malloc(sizeof(t_fd))))
		ft_error("add_fd: memory allocation failed");
	elem->file = ft_strdup(file);
	elem->fildes = fd;
	elem->next = NULL;
	tmp = *infildes;
	if (*infildes)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elem;
	}
	else
		*infildes = elem;
}

void			redil_proc(t_node *tree)
{
	char	*file;
	int		fd;
	t_data	*data;

	file = ft_strtrim(tree->left->word);
	data = init_data();
	if (data->tmp_fdin == -1)
		get_tmpfd(&data->tmp_fdin, "/.temp_in");
	if (data->tmp_fdin != -1 && (fd = check_file(file)) != -1)
	{
		add_infildes(&data->infildes, file, fd);
		read_tree(tree->right);
	}
	else
		update_data(&data);
	ft_strdel(&file);
}
