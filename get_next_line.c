/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/02 20:11:39 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/22 20:08:56 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*ft_line_read(char *str, int fin)
{
	size_t		i;
	char		*line;

	i = 0;
	while (str[i] != fin)
		i++;
	line = ft_strnew(i);
	i = 0;
	while (str[i] != fin)
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char		*organize_str(char *str)
{
	char	*new_str;
	int		i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if ((str[i] && !str[i + 1]) || !str[i])
	{
		ft_strdel(&str);
		return (NULL);
	}
	new_str = ft_strdup(str + i + 1);
	ft_strdel(&str);
	return (new_str);
}

int				get_next_line(int const fd, char **line)
{
	char			buf[BUF_SIZE + 1];
	char			*tmp;
	int				ret;
	char			*ptr;
	static char		*str;

	if (!str)
		str = ft_strnew(1);
	ret = 2;
	while ((tmp = str) && !(ft_strchr(tmp, '\n')))
	{
		if ((ret = read(fd, buf, BUF_SIZE)) == -1 || BUF_SIZE <= 0)
			return (-1);
		buf[ret] = '\0';
		ptr = str;
		str = ft_strjoin(str, buf);
		free(ptr);
		if (ret == 0 && *str == '\0')
			return (0);
		else if (ret == 0 && *str)
			break ;
	}
	*line = ft_line_read(str, ret > 0 ? '\n' : '\0');
	str = organize_str(str);
	return (1);
}
