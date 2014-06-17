/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/03 18:32:08 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/10 16:55:51 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static t_key	init_key(char *keyword, void *apply_key)
{
	t_key		key;

	key.keyword = ft_strdup(keyword);
	key.apply_key = apply_key;
	return (key);
}

t_key			*init_keytab(int set)
{
	static t_key	*key_tab = NULL;

	if (!key_tab && set == 1)
	{
		if (!(key_tab = (t_key *)malloc(sizeof(t_key) * KEY_NUM)))
			ft_error(ERROR(SH, E_MEMALLOC), "(initializing keytab)", 'y');
		key_tab[0] = init_key("\012", &apply_return);
		key_tab[1] = init_key("\033[A", &apply_arrowup);
		key_tab[2] = init_key("\033[B", &apply_arrowdown);
		key_tab[3] = init_key("\033[D", &apply_arrowleft);
		key_tab[4] = init_key("\033[C", &apply_arrowright);
		key_tab[5] = init_key("\177", &apply_delete);
		key_tab[6] = init_key("\033[3~", &apply_delete);
		key_tab[7] = init_key("\033\033[A", &apply_moveup);
		key_tab[8] = init_key("\033\033[B", &apply_movedown);
		key_tab[9] = init_key("\033\033[D", &apply_moveleft);
		key_tab[10] = init_key("\033\033[C", &apply_moveright);
		key_tab[11] = init_key("\033[H", &apply_movebegin);
		key_tab[12] = init_key("\033[F", &apply_moveend);
		key_tab[13] = init_key("\004", &apply_eof);
	}
	return (key_tab);
}

void			del_keytab(void)
{
	int		i;
	t_key	*key_tab;

	i = 0;
	key_tab = init_keytab(0);
	if (key_tab)
	{
		while (i < KEY_NUM)
		{
			ft_strdel(&(key_tab[i].keyword));
			i++;
		}
		free(key_tab);
		key_tab = NULL;
	}
}

void			minishell(void)
{
	char		*buf;
	int			i;
	t_key		*key_tab;

	i = 0;
	catch_signal();
	buf = ft_strnew(7);
	key_tab = init_keytab(0);
	while (read(0, buf, 6))
	{
		while (i < KEY_NUM)
		{
			if (!ft_strcmp(buf, key_tab[i].keyword))
			{
				key_tab[i].apply_key();
				break ;
			}
			i++;
		}
		if (ft_isprint(buf[0]))
			apply_edit(buf[0]);
		i = 0;
		ft_bzero(buf, ft_strlen(buf));
	}
}
