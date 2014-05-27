/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operand_fct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 15:34:23 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/14 20:40:43 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_ope			init_operand(int prio, char *name)
{
	t_ope	operand;

	operand.prio = prio;
	operand.name = name;
	return (operand);
}

t_ope			*init_opetab(void)
{
	static t_ope	*ope_tab = NULL;

	if (!ope_tab)
	{
		if (!(ope_tab = (t_ope *)malloc(sizeof(t_ope) * OPE_NUM)))
			ft_error("init_opetab: memory allocation failed");
		ope_tab[0] = init_operand(0, ft_strdup(";"));
		ope_tab[1] = init_operand(2, ft_strdup("|"));
		ope_tab[2] = init_operand(3, ft_strdup(">>"));
		ope_tab[3] = init_operand(3, ft_strdup(">"));
		ope_tab[4] = init_operand(3, ft_strdup("<"));
	}
	return (ope_tab);
}

t_ope			check_operand(char *type)
{
	int		i;
	t_ope	ope_null;
	t_ope	*ope_tab;

	i = 0;
	ope_tab = init_opetab();
	ope_null = init_operand(-1, NULL);
	while (i < OPE_NUM)
	{
		if (!ft_strncmp(type, ope_tab[i].name, ft_strlen(ope_tab[i].name)))
			return (ope_tab[i]);
		i++;
	}
	return (ope_null);
}

void			del_opetab(void)
{
	int		i;
	t_ope	*ope_tab;

	i = 0;
	ope_tab = init_opetab();
	if (ope_tab)
	{
		while (i < OPE_NUM)
		{
			ft_strdel(&ope_tab[i].name);
			i++;
		}
		free(ope_tab);
		ope_tab = NULL;
	}
}
