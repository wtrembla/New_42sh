/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/18 22:36:06 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/18 23:33:59 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		parse_toklist(t_token *toklist)
{
	int			ret;
	t_token		*ptmp;
	t_token		*tmp;

	ret = 1;
	ptmp = NULL;
	tmp = toklist;
	while (tmp)
	{
		if ((!ft_strcmp(tmp->type, ";") || !ft_strcmp(tmp->type, ">")
			|| !ft_strcmp(tmp->type, "<") || !ft_strcmp(tmp->type, ">>")
			|| !ft_strcmp(tmp->type, "|"))
			&& (!ptmp || (ptmp && !ptmp->word) || !tmp->next
				|| (tmp->next && !tmp->next->word)))
		{
			ft_putjoin_fd("ft_sh2: parse error near: ", tmp->type, 2);
			ret = 0;
			break ;
		}
		ptmp = tmp;
		tmp = tmp->next;
	}
	return (ret);
}
