/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/25 14:34:02 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/25 16:58:02 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void		set_var(char *av)
{
	char	**split;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	split = ft_strsplit(av, '=');
	tmp1 = ft_strjoin("setenv ", split[0]);
	tmp2 = ft_strjoin(tmp1, " ");
	tmp3 = ft_strjoin(tmp2, split[1]);
	apply_setenv(tmp3);
	del_av(split);
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
	ft_strdel(&tmp3);
}

static int		search_option(char *av, int *i)
{
	char	msg[2];
	int		j;

	j = 1;
	msg[1] = '\0';
	while (av[j])
	{
		if (av[j] != 'i')
		{
			*i = 0;
			msg[0] = av[j];
			ft_error(ERROR(ENV, E_ILLEGALOPT), msg, 'n');
			ft_putendl_fd(
				"usage: env [-i] [name=value ...] [utility [argument ...]]", 2);
			return (1);
		}
		else
		{
			if (av[j] == 'i')
				*i = 1;
		}
		j++;
	}
	return (0);
}

char			**parse_env(char **av, int *i)
{
	int		j;

	j = 1;
	while (av[j])
	{
		if (av[j][0] != '-')
			break ;
		else if (av[j][0] == '-' && search_option(av[j], i))
			return (NULL);
		j++;
	}
	return (av + j);
}

char			**change_var(char **av)
{
	int		i;

	i = 0;
	while (av[i])
	{
		if (strchr(av[i], '='))
			set_var(av[i]);
		else
			break ;
		i++;
	}
	return (av + i);
}

void			empty_env(t_env **env)
{
	(*env)->env = NULL;
}
