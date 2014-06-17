/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unsetenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/24 15:06:42 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/11 18:32:36 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int		var_isvalid(char *av, char **env)
{
	int		i;

	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(av, env[i], ft_strlen(av)))
			return (1);
		i++;
	}
	return (0);
}

static void		del_var(char *av, t_env **env)
{
	char	**uenv;
	int		i;
	int		j;

	i = 0;
	j = -1;
	while ((*env)->env && (*env)->env[i])
		i++;
	if (!(uenv = (char **)malloc(sizeof(char *) * i)))
	{
		ft_error(ERROR(UNSETENV, E_MEMALLOC), "(deleting variable)", 'n');
		return ;
	}
	while ((*env)->env && (*env)->env[++j]
			&& ft_strncmp(av, (*env)->env[j], ft_strlen(av)))
		uenv[j] = ft_strdup((*env)->env[j]);
	while ((*env)->env && (*env)->env[j + 1])
	{
		uenv[j] = ft_strdup((*env)->env[j + 1]);
		j++;
	}
	uenv[j] = NULL;
	del_av((*env)->env);
	(*env)->env = uenv;
}

void			apply_unsetenv(char *command)
{
	char	**av;
	int		i;
	int		size;
	t_env	*env;

	i = 1;
	av = ft_strsplit(command, ' ');
	size = av_size(av);
	env = init_env(NULL, 0);
	if (size < 2)
		ft_error(ERROR(UNSETENV, E_FEWARGS), NULL, 'n');
	else
	{
		while (i < size)
		{
			if (var_isvalid(av[i], env->env))
				del_var(av[i], &env);
			i++;
		}
		g_pid.built = 1;
	}
	if (g_pid.built == -1)
		g_pid.built = 0;
	del_av(av);
}
