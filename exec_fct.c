/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/15 21:09:35 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/25 17:30:14 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void		exec_pipe(char **av, int fd_out)
{
	t_data	*data;

	data = init_data(0);
	if (data->tmp_fdin != -1)
		write_pipefile();
	else
	{
		if ((g_pid.father = fork()) == -1)
			ft_error(ERROR(SH, E_CALLSYS), "fork", 'n');
		else
		{
			if (g_pid.father)
				wait(&g_pid.id);
			if (!g_pid.father)
			{
				dup2(data->tmp_pipeout, 0);
				dup2(fd_out, 1);
				if (execve(av[0], av, init_env(NULL, 0)->env) == -1)
					ft_error(ERROR(SH, E_NOCMD), av[0], 'y');
			}
		}
	}
}

static void		exec_child(char **av, int fd_out)
{
	t_data	*data;

	data = init_data(0);
	if (data->tmp_pipeout != -1)
		dup2(data->tmp_pipeout, 0);
	else if (data->tmp_fdin != -1)
		dup2(data->tmp_fdin, 0);
	dup2(fd_out, 1);
	if (execve(av[0], av, init_env(NULL, 0)->env) == -1)
		ft_error(ERROR(SH, E_NOCMD), av[0], 'y');
}

void			exec_command(char **av, int fd_out)
{
	t_data	*data;

	data = init_data(0);
	if (data->tmp_pipeout != -1)
		exec_pipe(av, fd_out);
	if (data->tmp_fdin != -1 || (data->tmp_fdin == -1
								&& data->tmp_pipeout == -1))
	{
		if (data->tmp_fdin != -1 && data->tmp_pipeout == -1)
			write_redilfile();
		if ((g_pid.father = fork()) == -1)
			ft_error(ERROR(SH, E_CALLSYS), "fork", 'n');
		else
		{
			if (g_pid.father)
				wait(&g_pid.id);
			if (!g_pid.father)
				exec_child(av, fd_out);
		}
	}
}
