/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibakayok <ibakayok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/29 19:36:46 by ibakayok          #+#    #+#             */
/*   Updated: 2014/04/15 17:09:21 by ibakayok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		bis(char const *s)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (s[n] == ' ' || s[n] == '\n' || s[n] == '\t')
		n++;
	while (s[n])
	{
		n++;
		i++;
	}
	while (s[n] == ' ' || s[n] == '\n' || s[n] == '\t' || s[n] == '\0')
	{
		n--;
		i--;
	}
	return (i);
}

int		bis2(char const *s)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while (s[n] == ' ' || s[n] == '\n' || s[n] == '\t')
		n++;
	while (s[n])
	{
		n++;
		i++;
	}
	while (s[n] == ' ' || s[n] == '\n' || s[n] == '\t' || s[n] == '\0')
	{
		n--;
		i--;
	}
	return (n);
}

char	*ft_strtrim(char const *s)
{
	char	*ret;
	int		i;
	int		n;

	ret = ft_strnew(ft_strlen(s));
	if (s != NULL)
	{
		i = bis(s);
		n = bis2(s);
		if (ret == NULL)
			return (NULL);
		ret[i + 1] = '\0';
		while (i > 0)
		{
			ret[i] = s[n];
			i--;
			n--;
		}
		ret[i] = s[n];
	}
	return (ret);
}
