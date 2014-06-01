/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lemchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibakayok <ibakayok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/22 16:18:45 by ibakayok          #+#    #+#             */
/*   Updated: 2014/02/23 21:16:36 by ibakayok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_xtiret(char *str, int i)
{
	int		r;
	char	*ret;

	r = 1;
	ret = (char *)malloc(sizeof(char) * ft_strlen(str));
	while (r < i && *str)
	{
		if (*str == '-')
			r++;
		str++;
	}
	r = 0;
	while (*str)
	{
		if (*str == '-')
		{
			ret[r] = '\0';
			return (ret);
		}
		ret[r] = *str;
		r++;
		str++;
	}
	ret[r] = '\0';
	return (ret);
}

char	*ft_xword(char *str, int i)
{
	int		r;
	char	*ret;

	r = 1;
	ret = (char *)malloc(sizeof(char) * ft_strlen(str));
	while (r < i && *str)
	{
		if (*str == ' ' || *str == '\t')
			r++;
		str++;
	}
	r = 0;
	while (*str)
	{
		if (*str == ' ' || *str == '\t')
		{
			ret[r] = '\0';
			return (ret);
		}
		ret[r] = *str;
		r++;
		str++;
	}
	ret[r] = '\0';
	return (ret);
}

int		is_tiret(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == '-')
			i++;
		str++;
	}
	return (i);
}
