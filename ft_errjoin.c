/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/31 16:03:50 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/15 21:03:19 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_errjoin(char *str1, char *str2)
{
	char	*join;

	join = ft_strjoin(str1, str2);
	ft_putendl_fd(join, 2);
	ft_strdel(&join);
	del_env();
	del_builtin();
	del_opetab();
	del_proctab();
	del_data();
	exit(0);
}
