/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 11:57:18 by wtrembla          #+#    #+#             */
/*   Updated: 2013/12/13 18:29:33 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	while (n--)
	{
		if (*(char *)s2 == c)
		{
			*(char *)s1 = *(char *)s2;
			return ((char *)s1 + 1);
		}
		else
			*(char *)s1++ = *(char *)s2++;
	}
	return (0);
}
