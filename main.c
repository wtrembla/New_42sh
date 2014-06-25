/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/22 13:56:17 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/25 18:17:17 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_env		*init_env(char **environ, int set)
{
	static t_env	*env = NULL;

	if (!env && set == 1)
	{
		if (!(env = (t_env *)malloc(sizeof(t_env))))
			ft_error(ERROR(SH, E_MEMALLOC), "(initializing env)", 'y');
		env->env = copy_env(environ);
		env->path = copy_path(environ);
		env->pwd = copy_pwd(environ);
		env->oldpwd = copy_oldpwd(environ);
		env->home = copy_home(environ);
		env->flagp = 0;
		env->optp = 0;
	}
	return (env);
}

void		del_env(void)
{
	t_env	*env;

	env = init_env(NULL, 0);
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
	if (!ft_strncmp(init_env(NULL, 0)->pwd, init_env(NULL, 0)->home,
					ft_strlen(init_env(NULL, 0)->home)))
	{
		ft_putstr("$ ~");
		ft_putendl(init_env(NULL, 0)->pwd + ft_strlen(init_env(NULL, 0)->home));
		ft_putstr("> ");
	}
	else
	{
		ft_putstr("$ ");
		ft_putendl(init_env(NULL, 0)->pwd);
		ft_putstr("> ");
	}
}

int			main(void)
{
	extern char		**environ;

	if (tgetent(NULL, getenv("TERM")) < 1)
		ft_error(ERROR(SH, E_IMPENV), NULL, 'y');
	init_pid();
	init_builtin(1);
	init_env(environ, 1);
	init_opetab(1);
	init_proctab(1);
	init_data(1);
	init_historic(1);
	init_keytab(1);
	apply_term(1);
	display_prompt();
	minishell();
	return (0);
}
