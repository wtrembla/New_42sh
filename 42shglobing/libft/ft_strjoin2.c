/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibakayok <ibakayok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/31 16:33:36 by ibakayok          #+#    #+#             */
/*   Updated: 2014/05/31 16:38:42 by ibakayok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin2(char **s1, char *s2)
{
	char		*ret;

	if (*s1 == NULL && s2 == NULL)
		return (NULL);
	if (*s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(*s1));
	ret = ft_strnew(ft_strlen(*s1) + ft_strlen(s2) + 1);
	ret = ft_strcat(ft_strcat(ft_strcpy(ret, *s1), " "), s2);
	ft_strdel(s1);
	return (ret);
}
