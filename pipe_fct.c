/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 14:48:38 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/27 18:27:54 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void			write_pipefile(void)
{
	char	*line;
	t_data	*data;
    t_fd	*tmp;

	data = init_data();
	tmp = data->infildes;
	lseek(data->tmp_pipeout, data->offset, SEEK_SET);
	while (tmp)
	{
		while (get_next_line(tmp->fildes, &line) > 0)
		{
			ft_putendl_fd(line, data->tmp_pipeout);
			ft_strdel(&line);
		}
		tmp = tmp->next;
	}
	lseek(data->tmp_pipeout, 0, SEEK_SET);
}

void			update_offset(t_data **data, off_t offset)
{
	(*data)->offset = offset;
}

static void		pipe_left(t_node *tree, int *pipe_fd, t_data *data)
{
	char	*line;

	close(pipe_fd[0]);
	get_tmpfd(&data->tmp_pipein, "/.temp_pipein");
	read_tree(tree->left);
	lseek(data->tmp_pipein, 0, SEEK_SET);
	while (get_next_line(data->tmp_pipein, &line) > 0)
	{
		ft_putendl_fd(line, pipe_fd[1]);
		ft_strdel(&line);
	}
	remove_tmp("/.temp_pipein");
	exit(EXIT_SUCCESS);
}

static void		pipe_right(t_node *tree, int *pipe_fd, t_data *data)
{
	char	*line;
	off_t	offset;

	close(pipe_fd[1]);
	if (data->tmp_pipeout == -1)
		get_tmpfd(&data->tmp_pipeout, "/.temp_pipeout");
	else
	{
		remove_tmp("/.temp_pipeout");
		get_tmpfd(&data->tmp_pipeout, "/.temp_pipeout");
	}
	while (get_next_line(pipe_fd[0], &line) > 0)
	{
		ft_putendl_fd(line, data->tmp_pipeout);
		ft_strdel(&line);
	}
	offset = lseek(data->tmp_pipeout, 0, SEEK_CUR);
	lseek(data->tmp_pipeout, 0, SEEK_SET);
	update_offset(&data, offset);
	read_tree(tree->right);
	remove_tmp("/.temp_pipeout");
	exit(EXIT_SUCCESS);
}

void			pipe_proc(t_node *tree)
{
	int		id;
	int		pipe_fd[2];
	t_data	*data;


	data = init_data();
	if (pipe(pipe_fd) == -1)
		ft_putendl_fd("42sh: pipe_proc: call system pipe error", 2);
	else
	{
		g_pid.child = fork();
		if (g_pid.child == 0)
			pipe_left(tree, pipe_fd, data);
		g_pid.father = fork();
		if (g_pid.father == 0)
			pipe_right(tree, pipe_fd, data);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		waitpid(g_pid.child, &id, 0);
		waitpid(g_pid.father, &g_pid.id, 0);
	}
}
