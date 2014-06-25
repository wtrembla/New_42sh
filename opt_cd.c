/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/17 15:18:10 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/25 17:22:37 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void			set_option(t_env **env)
{
	if ((*env)->flagp == 1)
		(*env)->optp = 1;
	else if ((*env)->flagp == -1)
		(*env)->optp = 0;
}

void			set_flag(t_env **env, int set)
{
	if (set == 1)
		(*env)->flagp = 1;
	else if (set == -1)
		(*env)->flagp = -1;
	else if (set == 0)
		(*env)->flagp = 0;
}

int				parse_cd(char **av)
{
	int		ret;
	int		size;
	t_env	*env;

	ret = 0;
	size = av_size(av);
	env = init_env(NULL, 0);
	if (size == 3 && (ft_strcmp(av[1], "-P") && ft_strcmp(av[1], "-L")))
	{
		ft_error(ERROR(CD, E_SYNTAX), NULL, 'n');
		g_pid.built = 0;
		ret = 1;
	}
	else if ((size == 3 && !ft_strcmp(av[1], "-P"))
				|| (size == 2 && !ft_strcmp(av[1], "-P")))
		set_flag(&env, 1);
	else if ((size == 3 && !ft_strcmp(av[1], "-L"))
				|| (size == 2 && !ft_strcmp(av[1], "-L")))
		set_flag(&env, -1);
	return (ret);
}
