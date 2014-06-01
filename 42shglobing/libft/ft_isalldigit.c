/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalldigit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibakayok <ibakayok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/09 15:20:14 by ibakayok          #+#    #+#             */
/*   Updated: 2014/03/14 17:11:19 by ibakayok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isalldigit(char *str)
{
	if (str[0] == '\0')
		return (0);
	while (*str != 0)
	{
		if (ft_isdigit((int)*str) == 0)
			return (0);
		str++;
	}
	return (1);
}
