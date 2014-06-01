/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibakayok <ibakayok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/29 15:43:55 by ibakayok          #+#    #+#             */
/*   Updated: 2014/04/15 17:06:14 by ibakayok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int		i;
	size_t	c;

	i = ft_strlen(s1);
	c = 0;
	while (s2[c] != '\0' && c < n)
	{
		s1[i] = s2[c];
		c++;
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
