/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirr_fct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 14:49:27 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/21 18:36:49 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "ft_minishell.h"

void	redirr_proc(t_node *tree)
{
	(void)tree;
/*	char	*file;
	int		fd;
	t_data	*data;

	file = ft_strtrim(tree->left->word);
	data = init_data();
	if ((fd = open(file, O_APPEND | O_WRONLY | O_CREAT, 0644)) == -1)
		ft_putjoin_fd("redir_proc: outfile not created: ", file, 2);
	else
		add_fd(&data->fildes, fd, file);
	ft_strdel(&file);
	read_tree(tree->right);
*/
	return ;
}
