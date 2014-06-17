/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/18 22:36:06 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/13 18:33:36 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int		parse_scolon(t_token *tmp)
{
	if (tmp->next && ft_strcmp(tmp->next->type, "com")
		&& ft_strcmp(tmp->next->type, ">") && ft_strcmp(tmp->next->type, "<")
						&& ft_strcmp(tmp->next->type, ">>"))
	{
		ft_error(ERROR(SH, E_PARSE), NULL, 'n');
		ft_putstr(tmp->type);
		ft_putstr(tmp->next->type);
		ft_putendl("'");
		return (1);
	}
	return (0);
}

static int		parse_redi(t_token *ptmp, t_token *tmp)
{
	if (!ptmp || (ptmp && ft_strcmp(ptmp->type, "com")))
	{
		if (tmp->next && tmp->next->next)
		{
			ft_error(ERROR(SH, E_PARSE), NULL, 'n');
			ft_putstr(tmp->next->next->type);
			ft_putendl("'");
		}
		else
		{
			ft_error(ERROR(SH, E_PARSE), NULL, 'n');
			ft_putendl("\\n'");
		}
		return (1);
	}
	return (0);
}

static int		parse_other(t_token *ptmp, t_token *tmp)
{
	if ((!tmp->next || (tmp->next && ft_strcmp(tmp->next->type, "com")
						&& ft_strcmp(tmp->next->type, ">")
						&& ft_strcmp(tmp->next->type, "<")
						&& ft_strcmp(tmp->next->type, ">>")))
		|| (!ptmp || (ptmp && ft_strcmp(ptmp->type, "com")
						&& ft_strcmp(ptmp->type, ">")
						&& ft_strcmp(ptmp->type, "<")
						&& ft_strcmp(ptmp->type, ">>"))))
	{
		ft_error(ERROR(SH, E_PARSE), NULL, 'n');
		ft_putstr(tmp->type);
		ft_putendl("'");
		return (1);
	}
	return (0);
}

int				parse_toklist(t_token *toklist)
{
	int			ret;
	t_token		*ptmp;
	t_token		*tmp;

	ret = 0;
	ptmp = NULL;
	tmp = toklist;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, ";"))
			ret = parse_scolon(tmp);
		else if (!ft_strcmp(tmp->type, ">") || !ft_strcmp(tmp->type, "<")
					|| !ft_strcmp(tmp->type, ">>"))
			ret = parse_redi(ptmp, tmp);
		else if (!ft_strcmp(tmp->type, "|") || !ft_strcmp(tmp->type, "||")
					|| !ft_strcmp(tmp->type, "&&"))
			ret = parse_other(ptmp, tmp);
		if (ret)
			break ;
		ptmp = tmp;
		tmp = tmp->next;
	}
	return (ret);
}
