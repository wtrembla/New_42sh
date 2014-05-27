/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 16:29:22 by wtrembla          #+#    #+#             */
/*   Updated: 2013/12/13 18:37:52 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (n == 0)
		return (1);
	if (*s1 == '\0' && *s2 == '\0')
		return (1);
	if (n == 1 && *s1 == *s2)
		return (1);
	if (*s1 == *s2 && n)
		return (ft_strnequ(s1 + 1, s2 + 1, n - 1));
	return (0);
}
