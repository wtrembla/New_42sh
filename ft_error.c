/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/09 20:26:19 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/06 20:04:44 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_error(char *str1, char *str2, char order)
{
	ft_putstr_fd(str1, 2);
	if (str2)
		ft_putendl_fd(str2, 2);
	if (order == 'y')
		apply_exit(NULL);
}
