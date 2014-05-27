/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 18:04:15 by wtrembla          #+#    #+#             */
/*   Updated: 2014/04/16 21:32:02 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putjoin(char *str1, char *str2)
{
	char	*join;

	join = ft_strjoin(str1, str2);
	ft_putendl(join);
	ft_strdel(&join);
}
