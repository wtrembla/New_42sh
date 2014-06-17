/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 18:49:44 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/10 17:22:38 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char		*reorganize_line(char *line, int i, int j)
{
	char	*new_line;
	int		k;

	k = 0;
	if (!(new_line = (char *)malloc(sizeof(char)
									* (ft_strlen(line) - (j - i) + 1))))
		ft_error(ERROR(SH, E_MEMALLOC), "(lexing line)", 'n');
	while (k < i)
	{
		new_line[k] = line[k];
		k++;
	}
	while (line[j])
	{
		new_line[k] = line[j];
		j++;
		k++;
	}
	new_line[k] = '\0';
	ft_strdel(&line);
	return (new_line);
}

static void		add_token(t_token **toklist, char *type, char *word, int prio)
{
	t_token	*elem;
	t_token	*tmp;

	if (!(elem = (t_token *)malloc(sizeof(t_token))))
		ft_error(ERROR(SH, E_MEMALLOC), "(adding token)", 'n');
	elem->type = ft_strdup(type);
	elem->word = ft_strdup(word);
	elem->prio = prio;
	elem->next = NULL;
	tmp = *toklist;
	if (*toklist)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elem;
	}
	else
		*toklist = elem;
}

char			*tokenize_redir(t_token **toklist, char *line)
{
	char	*word;
	int		i;
	int		j;
	t_ope	operand;

	i = 0;
	while (line[i] && !(operand = check_operand(line + i)).name)
		i++;
	j = i + ft_strlen(operand.name);
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	while (line[j] && line[j] != ' ' && line[j] != '\t')
		j++;
	word = ft_strsub(line, i + ft_strlen(operand.name),
						j - (i + ft_strlen(operand.name) - 1));
	if (word && *word)
		add_token(toklist, "com", word, -1);
	ft_strdel(&word);
	add_token(toklist, operand.name, NULL, operand.prio);
	return (reorganize_line(line, i, j));
}

char			*tokenize_other(t_token **toklist, char *line)
{
	char	*ndup;
	char	*word;
	char	*new_line;
	int		i;
	t_ope	operand;

	i = 0;
	while (line[i] && !(operand = check_operand(line + i)).name)
		i++;
	ndup = ft_strndup(line, i);
	word = ft_strtrim(ndup);
	ft_strdel(&ndup);
	if (word && *word)
		add_token(toklist, "com", word, -1);
	ft_strdel(&word);
	if (operand.name)
		add_token(toklist, operand.name, NULL, operand.prio);
	new_line = ft_strdup(line + i + ft_strlen(operand.name));
	ft_strdel(&line);
	return (new_line);
}
