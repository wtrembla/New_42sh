/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_notabspace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibakayok <ibakayok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 16:59:00 by ibakayok          #+#    #+#             */
/*   Updated: 2014/05/18 18:52:54 by ibakayok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_tab_spa(char *str)
{
	char	*tmp;
	int		i;
	int		p;

	i = 0;
	p = 0;
	tmp = (char *)malloc(sizeof(char) * ft_strlen(str));
	while (*str)
	{
		if ((*str == ' ' || *str == '	') && p == 0)
		{
			tmp[i++] = ' ';
			p = 1;
		}
		else if (!(*str == ' ' || *str == '	'))
		{
			tmp[i++] = *str;
			p = 0;
		}
		str++;
	}
	tmp[i] = '\0';
	return (tmp);
}
