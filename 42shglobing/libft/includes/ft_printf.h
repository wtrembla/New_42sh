/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibakayok <ibakayok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/19 19:31:10 by ibakayok          #+#    #+#             */
/*   Updated: 2014/02/09 16:20:01 by ibakayok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

int			ft_printf(const char *format, ...);
size_t		ft_strlen(const char *str);
int			ft_putstr(char *str);
int			ft_putnbr(int n);
int			ft_putchar(char c);

#endif
