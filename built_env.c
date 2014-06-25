/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 19:07:30 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/25 20:00:05 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void		aff_env(void)
{
	int		i;
	t_data	*data;
	t_env	*env;

	i = 0;
	data = init_data(0);
	env = init_env(NULL, 0);
	while (env->env && env->env[i])
	{
		if (data->tmp_pipein != -1)
			ft_putendl_fd(env->env[i], data->tmp_pipein);
		if (data->tmp_fdout != -1)
			ft_putendl_fd(env->env[i], data->tmp_fdout);
		if (data->tmp_fdout == -1 && data->tmp_pipein == -1)
			ft_putendl(env->env[i]);
		i++;
	}
	if (data->outfildes)
		write_redirfile();
}

static void		exec_utility(char **av)
{
	char	*tmp1;
	char	*tmp2;
	int		i;
	t_hist	**historic;

	i = 0;
	historic = init_historic(0);
	ft_strdel(&((*historic)->copy->line));
	while (av[i])
	{
		tmp1 = ft_strjoin((*historic)->copy->line, " ");
		tmp2 = ft_strjoin(tmp1, av[i]);
		ft_strdel(&((*historic)->copy->line));
		(*historic)->copy->line = ft_strdup(tmp2);
		ft_strdel(&tmp1);
		ft_strdel(&tmp2);
		i++;
	}
	apply_return();
}

static void		env_proc(char **av, int i)
{
	t_env	*env;

	env = init_env(NULL, 0);
	if ((g_pid.father = fork()) == -1)
		ft_error(ERROR(SH, E_CALLSYS), "fork", 'n');
	else if (g_pid.father)
		wait(&g_pid.id);
	else if (!g_pid.father)
	{
		av = change_var(av);
		if (!i && *av)
			exec_utility(av);
		else if (!i)
			aff_env();
		else
		{
			empty_env(&env);
			exec_utility(av);
		}
		if (g_pid.built == 0 || WEXITSTATUS(g_pid.id) != 0)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
}

void			apply_env(char *command)
{
	char	**av;
	char	**tmp;
	int		i;
	int		size;

	i = 0;
	av = ft_split(command);
	size = av_size(av);
	if ((tmp = parse_env(av, &i)))
	{
		if (size != 1)
			env_proc(tmp, i);
		else
			aff_env();
	}
	g_pid.built = tmp ? 1 : 0;
	del_av(av);
}
