/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibakayok <ibakayok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/22 20:51:01 by ibakayok          #+#    #+#             */
/*   Updated: 2014/04/15 18:12:20 by ibakayok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putnbr(int n)
{
	int		l;

	l = 1;
	if (n == -2147483648)
		ft_putstr("-2147483648");
	else
	{
		if (n < 0)
		{
			l++;
			ft_putchar('-');
			n *= -1;
		}
		if (n >= 10)
		{
			l += ft_putnbr(n / 10);
			l += ft_putnbr(n % 10);
		}
		else
			ft_putchar(48 + n);
	}
	return (l);
}
