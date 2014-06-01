/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibakayok <ibakayok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 13:27:53 by ibakayok          #+#    #+#             */
/*   Updated: 2014/05/28 16:36:33 by ibakayok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	ret;
	int		i;
	int		b;

	b = -1;
	ret = (char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ret)
			b = i;
		i++;
	}
	if (b != -1 && ret != '\0')
		return ((char *)&s[b]);
	else if (ret == '\0')
		return ((char *)&s[i]);
	else
		return (NULL);
}
