/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 13:40:36 by wtrembla          #+#    #+#             */
/*   Updated: 2013/12/13 18:29:50 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const void	*loc;

	loc = s;
	while (n--)
	{
		if (*(char *)loc == (unsigned char)c)
			return ((void *)loc);
		loc++;
	}
	return (NULL);
}
