/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 18:54:26 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/22 17:26:27 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_fig(int n)
{
	int		i;

	i = 1;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_fill_str(char *str, int n, int i)
{
	int		j;

	j = 0;
	if (n == -2147483648)
		n = -2147483647;
	if (n < 0)
	{
		n = -n;
		j++;
		str[0] = '-';
	}
	str[i] = '\0';
	while (--i >= j)
	{
		str[i] = n % 10 + 48;
		n = n / 10;
	}
	return (str);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		i;

	i = ft_count_fig(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (0);
	str = ft_fill_str(str, n, i);
	if (n == -2147483648)
		str[i - 1] = '8';
	return (str);
}
