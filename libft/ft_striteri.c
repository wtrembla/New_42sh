/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 16:05:03 by wtrembla          #+#    #+#             */
/*   Updated: 2013/12/13 18:35:59 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	char				*tmp;
	unsigned int		i;

	tmp = s;
	i = 0;
	while (*tmp)
	{
		f(i, tmp);
		tmp++;
		i++;
	}
}
