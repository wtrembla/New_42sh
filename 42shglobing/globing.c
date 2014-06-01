/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibakayok <ibakayok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/27 17:23:07 by ibakayok          #+#    #+#             */
/*   Updated: 2014/06/01 17:07:58 by ibakayok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "libft.h"

char	**ft_lastsplit(char *str, char c)
{
	char	**ret;
	int		i;

	ret = (char **)malloc(sizeof(char *) * 2);
	i = ft_strlen(str);
	while (str[i] != c && i > 0)
		i--;
	ret[0] = ft_strndup(str, i);
	ret[1] = ft_strdup(str + i);
	return (ret);
}

int		ft_patern(char *s1,char *s2)
{
	int		i;

	i = 0;
	while (s1[i] != '*' && s1[i])
		i++;
	if (ft_strncmp(s1,s2,(i - 1) == 0 && ft_strstr((s1 + i + 1), s2) != 0))
		return(1);
	return (0);
}

char	*ft_remp(char *str)
{
	DIR				*fichier;
	struct dirent	*lecture;
	char			**path;
	char			*ret;
	char			*tmp;

	path = ft_lastsplit(str, '/');
	fichier = opendir(path[0]);
	while((lecture = readdir(fichier)))
	{
		if (ft_patern(path[1], lecture->d_name) == 1)
		{
			tmp = ft_strjoin(path[0], lecture->d_name);
			ret = ft_strjoin2(&ret, tmp);
			ft_strdel(&tmp);
		}
	}
	return (ret);
}

char	**ft_glob(char *str)
{
	char	**data;
	char	*tmp;
	int		i;

	i = 0;
	data = ft_strsplit(str, ' ');
	while (data[i])
	{
		if (strchr(data[i], '*') != NULL)
		{
			tmp = ft_remp(data[i]);
			ft_strdel(&data[i]);
			data[i] = tmp;
		}
		i++;
	}
	return (data);
}

/*
**gcc -Wall -Wextra main.c globing.c -L libft/ -lft -I libft/includes
*/
