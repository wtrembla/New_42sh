/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/24 16:29:08 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/15 21:02:55 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	apply_exit(char *command)
{
	char	**av;
	int		ret;
	int		size;

	av = ft_split(command);
	ret = 0;
	if ((size = av_size(av)) > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return ;
	}
	else if (size == 1 && av[1])
		ret = ft_atoi(av[1]);
	del_builtin();
	del_env();
	del_opetab();
	del_proctab();
	del_data();
	del_av(av);
	exit(ret);
}
