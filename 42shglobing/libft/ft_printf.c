/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibakayok <ibakayok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/22 20:50:43 by ibakayok          #+#    #+#             */
/*   Updated: 2014/03/09 15:26:25 by ibakayok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

void	ft_mod(va_list *ap, int i, const char *format, int *l)
{
	if (format[i] == '%')
	{
		*l = *l + 1;
		write(1, "%", 1);
	}
	if (format[i] == 's')
		*l = *l + ft_putstr(va_arg(*ap, char *));
	if (format[i] == 'd')
		*l = *l + ft_putnbr(va_arg(*ap, int));
	if (format[i] == 'c')
	{
		*l = *l + 1;
		ft_putchar(va_arg(*ap, int));
	}
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		l;

	i = 0;
	l = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] != '%')
			l += ft_putchar(format[i]);
		else
		{
			i++;
			ft_mod(&ap, i, format, &l);
		}
		i++;
	}
	va_end(ap);
	return (l);
}
