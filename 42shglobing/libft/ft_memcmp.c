/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibakayok <ibakayok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 16:46:34 by ibakayok          #+#    #+#             */
/*   Updated: 2013/12/08 21:54:52 by ibakayok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*c1;
	const char	*c2;

	c1 = (const char *)s1;
	c2 = (const char *)s2;
	while (*c1 == *c2 && --n)
	{
		c1++;
		c2++;
	}
	return ((unsigned char)*c1 - (unsigned char)*c2);
}
