/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirr_fct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 14:49:27 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/11 19:40:31 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "ft_minishell.h"

static int		check_file(char *file)
{
	int		fd;

	fd = -1;
	if (!access(file, F_OK) && access(file, W_OK) == -1)
		ft_error(ERROR(SH, E_NOACCESS), file, 'n');
	else if ((fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
		ft_error(ERROR(SH, E_OPEN), file, 'n');
	return (fd);
}

void			redirr_proc(t_node *tree)
{
	char	*file;
	int		fd;
	t_data	*data;

	file = ft_strtrim(tree->left->word);
	data = init_data(0);
	if (data->tmp_fdout == -1)
		get_tmpfd(&data->tmp_fdout, "/.temp_out");
	if (data->tmp_fdout != -1 && (fd = check_file(file)) != -1)
	{
		add_outfildes(&data->outfildes, file, fd);
		read_tree(tree->right);
	}
	else
	{
		update_data(&data);
		g_pid.built = 0;
	}
	ft_strdel(&file);
}
