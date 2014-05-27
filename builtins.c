/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 18:26:55 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/13 17:48:11 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static t_built	init_built(char *name, void *apply_built)
{
	t_built		built;

	built.name = ft_strdup(name);
	built.apply_built = apply_built;
	return (built);
}

t_built			*init_builtin(void)
{
	static t_built	*builtin = NULL;

	if (!builtin)
	{
		if (!(builtin = (t_built *)malloc(sizeof(t_built) * BUILT_NUM)))
			ft_error("init_builtin: memory allocation failed");
		builtin[0] = init_built("cd", &apply_cd);
		builtin[1] = init_built("env", &apply_env);
		builtin[2] = init_built("exit", &apply_exit);
		builtin[3] = init_built("setenv", &apply_setenv);
		builtin[4] = init_built("unsetenv", &apply_unsetenv);
	}
	return (builtin);
}

int				check_builtin(char *command)
{
	char	**av;
	int		i;
	int		ret;
	t_built	*builtin;

	i = 0;
	ret = 0;
	av = ft_strsplit(command, ' ');
	builtin = init_builtin();
	while (i < BUILT_NUM)
	{
		if (!ft_strcmp(av[0], builtin[i].name))
		{
			builtin[i].apply_built(command);
			ret = 1;
		}
		i++;
	}
	del_av(av);
	return (ret);
}

void			del_builtin(void)
{
	int			i;
	t_built		*builtin;

	i = 0;
	builtin = init_builtin();
	if (builtin)
	{
		while (i < BUILT_NUM)
		{
			ft_strdel(&(builtin[i].name));
			i++;
		}
		free(builtin);
		builtin = NULL;
	}
}
