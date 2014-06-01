/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibakayok <ibakayok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/25 19:20:57 by ibakayok          #+#    #+#             */
/*   Updated: 2014/06/01 16:33:31 by ibakayok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(const char *s1, size_t n)
{
	size_t	len;
	char	*s2;

	len = ft_strlen(s1) + 1;
	if (len > n)
	{
		if ((s2 = ft_strnew(n)) == NULL)
			return (NULL);
		else
			ft_strncpy(s2, s1, n);
	}
	else
	{
		if ((s2 = ft_strnew(len)) == NULL)
			return (NULL);
		else
			ft_strncpy(s2, s1, len);
	}
	return (s2);
}

static int	ft_count_word(char const *s, char c)
{
	int		word;
	int		i;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			word++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (word);
}

static int	ft_len_word(char const *s, char c)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		j;
	int		len;
	int		word;

	j = -1;
	if (s == NULL)
		return (NULL);
	word = ft_count_word(s, c);
	if ((tab = (char **)malloc(sizeof(char *) * (word + 1))) == NULL)
		return (NULL);
	while (++j < word)
	{
		while (*s != '\0' && *s == c)
			s++;
		len = ft_len_word(s, c);
		tab[j] = ft_strndup(s, len);
		while (*s != '\0' && *s != c)
			s++;
	}
	tab[j] = '\0';
	return (tab);
}
