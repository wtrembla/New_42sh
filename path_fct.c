/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 16:39:16 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/13 17:49:59 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*build_path(char *path, char *command)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin(path, "/");
	tmp2 = ft_strjoin(tmp1, command);
	ft_strdel(&tmp1);
	return (tmp2);
}

int		check_path(char *path)
{
	if (access(path, F_OK) == -1)
		return (-1);
	if (access(path, X_OK) == -1)
		return (-2);
	return (0);
}
