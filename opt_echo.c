/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/17 19:11:30 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/18 19:30:19 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int		search_option(char *av, int *n, int *e, int *em)
{
	int		i;

	i = 1;
	while (av[i])
	{
		if (av[i] != 'n' && av[i] != 'e' && av[i] != 'E')
		{
			*n = 0;
			*e = 0;
			*em = 0;
			return (1);
		}
		else
		{
			if (av[i] == 'n')
				*n = 1;
			if (av[i] == 'e')
				*e = 1;
			if (av[i] == 'E')
				*em = 1;
		}
		i++;
	}
	return (0);
}

char			**parse_echo(char **av, int *n, int *e, int *em)
{
	int		i;

	i = 1;
	while (av[i])
	{
		if (av[i][0] != '-' || search_option(av[i], n, e, em))
			break ;
		i++;
	}
	return (av + i);
}
