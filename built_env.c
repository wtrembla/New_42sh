/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 19:07:30 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/11 18:26:28 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	apply_env(char *command)
{
	int		i;
	t_env	*env;

	i = 0;
	(void)command;
	env = init_env(NULL, 0);
	while (env->env && env->env[i])
	{
		ft_putendl(env->env[i]);
		i++;
	}
	g_pid.built = 1;
}
