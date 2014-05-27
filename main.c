/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/22 13:56:17 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/22 13:45:57 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_env		*init_env(char **environ)
{
	static t_env	*env = NULL;

	if (!env)
	{
		if (!(env = (t_env *)malloc(sizeof(t_env))))
			ft_error("init_env: memory allocation failed");
		env->env = copy_env(environ);
		env->path = copy_path(environ);
		env->pwd = copy_pwd(environ);
		env->oldpwd = copy_oldpwd(environ);
		env->home = copy_home(environ);
	}
	return (env);
}

void		del_env(void)
{
	t_env	*env;

	env = init_env(NULL);
	if (env)
	{
		del_av(env->env);
		del_av(env->path);
		ft_strdel(&env->pwd);
		ft_strdel(&env->oldpwd);
		ft_strdel(&env->home);
		free(env);
		env = NULL;
	}
}

void		display_prompt(void)
{
	if (ft_strstr(init_env(NULL)->pwd, init_env(NULL)->home))
	{
		ft_putstr("$ ~");
		ft_putendl(init_env(NULL)->pwd + ft_strlen(init_env(NULL)->home));
		ft_putstr("> ");
	}
	else
	{
		ft_putstr("$ ");
		ft_putendl(init_env(NULL)->pwd);
		ft_putstr("> ");
	}
}

int			main(void)
{
	extern char		**environ;

	init_pid();
	init_builtin();
	init_env(environ);
	init_opetab();
	init_proctab();
	init_data();
	display_prompt();
	minishell();
	return (0);
}
