/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/24 16:29:08 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/25 18:23:02 by wtrembla         ###   ########.fr       */
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
		ft_error(ERROR(EXIT, E_MANYARGS), NULL, 'n');
		g_pid.built = 0;
		return ;
	}
	else if (size == 1 && av[1])
		ret = ft_atoi(av[1]);
//	update_historic();
	del_builtin();
	del_env();
	del_opetab();
	del_proctab();
	del_data();
	del_historic();
	del_keytab();
	del_av(av);
	apply_term(-1);
	exit(ret);
}
