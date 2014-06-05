/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/03 20:22:02 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/03 20:25:03 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int     aff_c(int c)
{
//	int     fd;

//	if ((fd = open(ttyname(0), O_WRONLY)) == -1)
//		ft_error("aff_c: error opening new interface");
	write(0, &c, 1);
//	if (close(fd) == -1)
//		ft_error("aff_c: error closing new interface");
	return (0);
}

int     aff_str(char *str)
{
//	int     fd;

//	if ((fd = open(ttyname(0), O_WRONLY)) == -1)
//		ft_error("aff_str: error opening new interface");
	ft_putstr_fd(str, 0);
//	if (close(fd) == -1)
//		ft_error("aff_str: error closing new interface");
	return (0);
}
