/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/17 19:10:29 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/18 19:54:39 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char	*print_unprintable(char *str, char fin, int e, int em)
{
	while (*str && *str != fin)
	{
		if (*str == '\\' && *(str + 1))
		{
			if ((!em || (em && e)) && *(str + 1) == 't')
				ft_putchar('\t');
			else if ((!em || (em && e)) && *(str + 1) == 'v')
				ft_putchar('\v');
			else if ((!em || (em && e)) && *(str + 1) == 'n')
				ft_putchar('\n');
			else if ((!em || (em && e)) && *(str + 1) == 'e')
				ft_putchar('\e');
			else if ((!em || (em && e)) && *(str + 1) == 'b')
				ft_putchar('\b');
			else if ((!em || (em && e)) && *(str + 1) == 'f')
				ft_putchar('\f');
			else
			{
				ft_putchar(*str);
				ft_putchar(*(str + 1));
			}
			str += 2;
		}
		else
		{
			ft_putchar(*str);
			str++;
		}
	}
	if (*str)
		str++;
	return (str);
}

static void	print_str(char *str, int e, int em)
{
	char	*tmp;

	tmp = str;
	while (*tmp)
	{
		if (*tmp == '\"' || *tmp == '\'')
			tmp = print_unprintable(tmp + 1, *tmp, e, em);
		else
		{
			if (*tmp == '\\' && *(tmp + 1))
				ft_putchar(*(++tmp));
			else if (*tmp != '\\')
				ft_putchar(*tmp);
			tmp++;
		}
	}
}

void		apply_echo(char *command)
{
	char	**av;
	char	**tmp;
	int		n;
	int		e;
	int		em;

	n = 0;
	e = 0;
	em = 0;
	av = ft_split(command);
	tmp = parse_echo(av, &n, &e, &em);
	while (tmp && *tmp)
	{
		print_str(*tmp, e, em);
		if (*(tmp + 1))
			ft_putchar(' ');
		tmp++;
	}
	if (!n)
		ft_putchar('\n');
	del_av(av);
}
