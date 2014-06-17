/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_fct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 16:49:22 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/06 19:55:39 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	**copy_env(char **environ)
{
	char	**env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	env = NULL;
	while (environ && environ[i])
		i++;
	if (!(env = (char **)malloc(sizeof(char *) * (i + 1))))
		ft_error(ERROR(SH, E_MEMALLOC), "(copying env)", 'y');
	while (environ && environ[j])
	{
		env[j] = ft_strdup(environ[j]);
		j++;
	}
	env[j] = NULL;
	return (env);
}

char	**copy_path(char **environ)
{
	char	**path;
	int		i;

	i = 0;
	path = NULL;
	while (environ && environ[i] && ft_strncmp(environ[i], "PATH=", 5))
		i++;
	if (environ && environ[i])
		path = ft_strsplit(environ[i] + 5, ':');
	if (!path)
		ft_error(ERROR(SH, E_IMPENV), NULL, 'y');
	return (path);
}

char	*copy_oldpwd(char **environ)
{
	char	*oldpwd;
	int		i;

	i = 0;
	oldpwd = NULL;
	while (environ && environ[i] && ft_strncmp(environ[i], "OLDPWD=", 7))
		i++;
	if (environ && environ[i])
		oldpwd = ft_strdup(environ[i] + 7);
	if (!oldpwd)
		ft_error(ERROR(SH, E_IMPENV), NULL, 'y');
	return (oldpwd);
}

char	*copy_pwd(char **environ)
{
	char	*pwd;
	int		i;

	i = 0;
	pwd = NULL;
	while (environ && environ[i] && ft_strncmp(environ[i], "PWD=", 4))
		i++;
	if (environ && environ[i])
		pwd = ft_strdup(environ[i] + 4);
	if (!pwd)
		ft_error(ERROR(SH, E_IMPENV), NULL, 'y');
	return (pwd);
}

char	*copy_home(char **environ)
{
	char	*home;
	int		i;

	i = 0;
	home = NULL;
	while (environ && environ[i] && ft_strncmp(environ[i], "HOME=", 5))
		i++;
	if (environ && environ[i])
		home = ft_strdup(environ[i] + 5);
	if (!home)
		ft_error(ERROR(SH, E_IMPENV), NULL, 'y');
	return (home);
}
