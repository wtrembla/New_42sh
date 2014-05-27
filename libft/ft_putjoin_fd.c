/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putjoin_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 16:32:17 by wtrembla          #+#    #+#             */
/*   Updated: 2014/04/23 16:33:39 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putjoin_fd(char *str1, char *str2, int fd)
{
	char	*join;

	join = ft_strjoin(str1, str2);
	ft_putendl_fd(join, fd);
	ft_strdel(&join);
}
