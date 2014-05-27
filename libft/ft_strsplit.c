/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/26 12:35:24 by wtrembla          #+#    #+#             */
/*   Updated: 2014/04/29 16:17:56 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_str_count(char const *s, char c)
{
	int		i;

	i = 0;
	while (s && *s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			i++;
			while (*s && *s != c)
				s++;
		}
		s--;
		s++;
	}
	return (i);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**split;
	int		i;
	int		j;
	int		k;
	int		count;

	i = 0;
	j = 0;
	k = 0;
	count = ft_str_count(s, c);
	split = (char **)malloc(sizeof(char *) * (count + 1));
	if (split == NULL)
		return (0);
	while (i < count)
	{
		while (s[j] == c && s[j])
			j++;
		while (s[j + k] != c && s[j + k])
			k++;
		split[i++] = ft_strsub(s, (unsigned int)j, (size_t)k);
		j = j + k;
		k = 0;
	}
	split[i] = '\0';
	return (split);
}
