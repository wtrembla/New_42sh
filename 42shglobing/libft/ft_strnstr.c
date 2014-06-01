/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibakayok <ibakayok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 13:27:53 by ibakayok          #+#    #+#             */
/*   Updated: 2014/04/15 17:08:18 by ibakayok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	if (!(*s2))
		return ((char *)s1);
	while (*s1 && n > 0)
	{
		if (ft_strncmp(s1, s2, ft_strlen(s2)) == 0 && n >= ft_strlen(s2))
			return ((char *)s1);
		s1++;
		n--;
	}
	return (0);
}
