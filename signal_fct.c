/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_fct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/24 17:13:48 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/13 17:43:57 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <signal.h>

static void		handle_signal(int sig)
{
	if (g_pid.father || g_pid.child)
	{
		if (g_pid.father)
			kill(sig, g_pid.father);
		if (g_pid.child)
			kill(sig, g_pid.child);
	}
	else
	{
		if (sig == SIGINT)
		{
			ft_putchar('\n');
			display_prompt();
		}
		else
			signal(sig, SIG_IGN);
	}
}

void			init_pid(void)
{
	g_pid.id = 0;
	g_pid.father = 0;
	g_pid.child = 0;
	g_pid.built = -1;
}

void			catch_signal(void)
{
	int		i;

	i = 0;
	while (i < 33)
	{
		if (i == 2)
			signal(i, handle_signal);
		else
			signal(i, SIG_IGN);
		i++;
	}
}
