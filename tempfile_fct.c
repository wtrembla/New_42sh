/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tempfile_fct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/22 13:05:15 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/27 18:29:00 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "ft_minishell.h"

static char		**get_cmd(char *tmp_file)
{
	char	**cmd;
	char	*tmp;
	char	*tmp_path;

	tmp_path = ft_strjoin(init_env(NULL)->home, tmp_file);
	tmp = ft_strjoin("rm -rf ", tmp_path);
	cmd = ft_split(tmp);
	ft_strdel(&tmp_path);
	ft_strdel(&tmp);
	return (cmd);
}

void			get_tmpfd(int *tmp_fd, char *tmp_file)
{
	char	*tmp_path;

	tmp_path = ft_strjoin(init_env(NULL)->home, tmp_file);
	if ((*tmp_fd = open(tmp_path, O_RDWR | O_TRUNC | O_CREAT, 0644)) == -1)
		ft_putendl_fd("42sh: get_tmpfd: temporary file not created", 2);
	ft_strdel(&tmp_path);
}

void			remove_tmp(char *tmp_file)
{
	char	**cmd;
	char	*cmd_path;
	pid_t	father;

	cmd = get_cmd(tmp_file);
	if ((cmd_path = check_command(cmd[0])))
	{
		if ((father = fork()) == -1)
			ft_putendl_fd("42sh: remove_tmp: call system fork error", 2);
		else
		{
			if (father)
				wait(0);
			if (father == 0)
			{
				if (execve(cmd_path, cmd, init_env(NULL)->env) == -1)
					ft_error("42sh: remove_tmp: temporary file not removed");
			}
		}
	}
	del_av(cmd);
	ft_strdel(&cmd_path);
}
