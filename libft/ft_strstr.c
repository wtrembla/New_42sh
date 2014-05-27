/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 17:13:24 by wtrembla          #+#    #+#             */
/*   Updated: 2014/01/31 16:38:43 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*s2 == '\0')
		return ((char *)s1);
	while (s1[i])
	{
		if (s1[i] == s2[0])
		{
			while (s1[i + j] == s2[j] && s2[j])
			{
				j++;
				if (j == ft_strlen(s2))
					return ((char *)(s1) + i);
			}
			j = 0;
		}
		i++;
	}
	return (0);
}
