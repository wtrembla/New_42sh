/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibakayok <ibakayok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/29 15:43:55 by ibakayok          #+#    #+#             */
/*   Updated: 2014/04/15 17:01:39 by ibakayok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	char		*p;
	const char	*t;

	p = s1;
	t = s2;
	if (s1 == '\0' || s2 == '\0')
		return (NULL);
	while (n--)
	{
		*p = *t;
		p++;
		t++;
		if (*(p - 1) == c)
			return ((void *)p);
	}
	return (NULL);
}
