/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/09 20:26:19 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/15 21:03:07 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	del_env();
	del_builtin();
	del_opetab();
	del_proctab();
	del_data();
	exit(EXIT_FAILURE);
}
