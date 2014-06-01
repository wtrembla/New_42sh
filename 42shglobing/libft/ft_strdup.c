/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibakayok <ibakayok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/29 15:43:55 by ibakayok          #+#    #+#             */
/*   Updated: 2014/04/15 17:04:29 by ibakayok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char			*ret;
	int				len;
	int				i;

	len = ft_strlen(s1);
	i = -1;
	if ((ret = (char *)malloc(sizeof(*ret) * (len + 1))) == NULL)
		return (NULL);
	while (++i < len)
		ret[i] = s1[i];
	ret[i] = 0;
	return (ret);
}
