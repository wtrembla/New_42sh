/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/15 20:01:14 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/27 14:36:43 by wtrembla         ###   ########.fr       */
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
	else if ((fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		ft_putjoin_fd("42sh: check_file: open error: ", file, 2);
	return (fd);
}

void			write_redirfile(char *file)
{
	char	*line;
	int		fd;
	t_data	*data;

	data = init_data();
	lseek(data->tmp_fdout, 0, SEEK_SET);
	if ((fd = open(file, O_WRONLY | O_TRUNC)) == -1)
		ft_putendl_fd("Erreur1", 2);
	while (get_next_line(data->tmp_fdout, &line) > 0)
	{
		ft_putendl_fd(line, fd);
		ft_strdel(&line);
	}
	if (close(fd) == -1)
		ft_putendl_fd("Erreur2", 2);
}

void			add_outfildes(t_fd **outfildes, char *file, int fd)
{
	t_fd	*elem;
	t_fd	*tmp;

	if (!(elem = (t_fd *)malloc(sizeof(t_fd))))
		ft_error("add_fd: memory allocation failed");
	elem->file = ft_strdup(file);
	elem->fildes = fd;
	elem->next = NULL;
	tmp = *outfildes;
	if (*outfildes)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elem;
	}
	else
		*outfildes = elem;
}

void			redir_proc(t_node *tree)
{
	char	*file;
	int		fd;
	t_data	*data;

	file = ft_strtrim(tree->left->word);
	data = init_data();
	if (data->tmp_fdout == -1)
		get_tmpfd(&data->tmp_fdout, "/.temp_out");
	if (data->tmp_fdout != -1 && (fd = check_file(file)) != -1)
	{
		add_outfildes(&data->outfildes, file, fd);
		read_tree(tree->right);
	}
	else
		update_data(&data);
	ft_strdel(&file);
}
