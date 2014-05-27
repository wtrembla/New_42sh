/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 15:55:00 by wtrembla          #+#    #+#             */
/*   Updated: 2013/12/13 18:37:16 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*tmp;
	size_t	i;

	tmp = s1;
	i = 0;
	while (*tmp)
		tmp++;
	while (s2[i] != '\0' && i < n)
	{
		tmp[i] = s2[i];
		i++;
	}
	tmp[i] = '\0';
	return (s1);
}
