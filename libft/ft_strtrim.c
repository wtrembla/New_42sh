/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 16:49:48 by wtrembla          #+#    #+#             */
/*   Updated: 2013/12/13 18:39:35 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_trimend(char const *s)
{
	size_t	i;

	i = ft_strlen(s) - 1;
	if (*s == '\0')
		return (0);
	while (s[i] == ' ' || s[i] == '\n'
		|| s[i] == '\t')
	{
		if (i == 0)
			return (0);
		i--;
	}
	return (i + 1);
}

static int	ft_trimstart(char const *s)
{
	size_t	i;

	i = 0;
	if (*s == '\0')
		return (0);
	while (s[i] == ' ' || s[i] == '\n'
		|| s[i] == '\t')
	{
		if (i == ft_strlen(s) - 1)
			return (0);
		i++;
	}
	return (i);
}

char		*ft_strtrim(char const *s)
{
	int				len;
	char			*str;
	unsigned int	start;

	if (!s)
		return (0);
	len = (size_t)ft_trimend(s) - (size_t)ft_trimstart(s);
	start = (unsigned int)(ft_trimstart(s));
	str = ft_strsub(s, start, len);
	return (str);
}
