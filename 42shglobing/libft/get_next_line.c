/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibakayok <ibakayok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/03 15:09:26 by ibakayok          #+#    #+#             */
/*   Updated: 2014/04/15 17:12:43 by ibakayok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

static int		ft_isnewline(char *str)
{
	while (*str != '\0' && *str != '\n')
		str++;
	if (*str == '\0')
		return (0);
	return (1);
}

static int		ft_realloc(char **line, int size, int i)
{
	char		*temp;

	if (i == 1)
	{
		if (*line == NULL)
			free(*line);
		*line = ft_strnew(size);
		return (0);
	}
	else
	{
		temp = ft_strdup(*line);
		free(*line);
		*line = ft_strnew(ft_strlen(temp) + size);
		ft_strcpy(*line, temp);
		free(temp);
		return (0);
	}
}

static int		blocdingue(char **tmp, char **line, char *bf, int *p)
{
	char		*temp;

	if (*tmp != NULL && ft_isnewline(*tmp) != 1)
	{
		temp = ft_strdup(*line);
		free(*line);
		*line = ft_strnew(ft_strlen(temp) + ft_strlen(*tmp));
		ft_strcpy(*line, *tmp);
		ft_strcat(*line, temp);
		free(temp);
	}
	free(*tmp);
	*line = ft_strjoin(*line, ft_strsub(bf, 0, ft_strchr(bf, '\n') - bf));
	*p = 1;
	*tmp = ft_strdup(ft_strchr(bf, '\n') + 1);
	return (1);
}

static int		blocfaible(char **line, char **tmp, int *p)
{
	*line = ft_strsub(*tmp, 0, ft_strchr(*tmp, '\n') - *tmp);
	*tmp = ft_strdup(ft_strchr(*tmp, '\n') + 1);
	*p = 1;
	return (1);
}

int				get_next_line(int const fd, char **line)
{
	int			ret;
	char		bf[BUFF_SIZE + 1];
	static char	*tmp;
	static int	p = 1;

	p = ft_realloc(line, BUFF_SIZE + 1, p);
	if (tmp != NULL && ft_isnewline(tmp) == 1)
		return (blocfaible(line, &tmp, &p));
	if ((ret = read(fd, bf, BUFF_SIZE)) == -1)
		return (-1);
	bf[ret] = '\0';
	if (ft_isnewline(bf) == 1 && ret != 0)
		return (blocdingue(&tmp, line, bf, &p));
	else if (ret == 0)
	{
		*line = ft_strjoin(*line, bf);
		return (0);
	}
	else
	{
		*line = ft_strcat(*line, bf);
		return (get_next_line(fd, line));
	}
}
