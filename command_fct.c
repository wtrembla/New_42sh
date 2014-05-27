/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_fct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 15:47:16 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/27 18:28:41 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void		improper_command(int ret, char *command)
{
	if (ret == -1 && (!ft_strncmp(command, "./", 2)
					|| !ft_strncmp(command, "../", 3) || command[0] == '/'))
		ft_putjoin_fd("ft_sh1: no such file or directory: ", command, 2);
	else if (ret == -1)
		ft_putjoin_fd("ft_sh1: command not found: ", command, 2);
	else if (ret == -2)
		ft_putjoin_fd("ft_sh1: permission denied: ", command, 2);
}

char			*check_command(char *command)
{
	char	*tmp;
	int		i;
	int		ret;
	t_env	*env;

	ret = 0;
	env = init_env(NULL);
	tmp = NULL;
	if ((!ft_strncmp(command, "./", 2) || !ft_strncmp(command, "../", 3)
		|| command[0] == '/') && !(ret = check_path(command)))
		return (ft_strdup(command));
	else if (!ret)
	{
		i = -1;
		while (env->path[++i])
		{
			ft_strdel(&tmp);
			tmp = build_path(env->path[i], command);
			if (!(ret = check_path(tmp)))
				return (tmp);
		}
	}
	improper_command(ret, command);
	ft_strdel(&tmp);
	return (NULL);
}

static void		run_command(char **av, t_data *data)
{
	t_fd	*tmp;

	if (data->tmp_pipein != -1)
		exec_command(av, data->tmp_pipein);
	if (data->tmp_fdout != -1)
	{
		exec_command(av, data->tmp_fdout);
		if (data->outfildes)
		{
			tmp = data->outfildes;
			while (tmp)
			{
				write_redirfile(tmp->file);
				tmp = tmp->next;
			}
		}
	}
	else if (data->tmp_pipein == -1)
		exec_command(av, 1);
}

void			command_proc(char *command)
{
	char	**av;
	char	*tmp;
	t_data	*data;

	init_pid();
	av = ft_split(command);
	data = init_data();
	if (av && (tmp = check_command(av[0])))
	{
		ft_strdel(&av[0]);
		av[0] = tmp;
		run_command(av, data);
	}
	update_data(&data);
	del_av(av);
}
