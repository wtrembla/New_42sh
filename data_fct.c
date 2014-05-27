/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/15 20:51:58 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/27 15:26:01 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void		del_fildes(t_fd **fildes)
{
	if (*fildes)
	{
		del_fildes(&((*fildes)->next));
		ft_strdel(&((*fildes)->file));
		free(*fildes);
		*fildes = NULL;
	}
}

static void		close_fildes(t_fd *fildes)
{
	t_fd	*tmp;

	tmp = fildes;
	if (fildes)
	{
		while (tmp)
		{
			if (close(tmp->fildes) == -1)
				ft_putjoin_fd("42sh: close fildes: close error: "
								, tmp->file, 2);
			tmp = tmp->next;
		}
	}
}

void			update_data(t_data **data)
{
	if ((*data)->tmp_fdin != -1)
	{
		if (close((*data)->tmp_fdin) == -1)
			ft_putendl_fd("42sh: update_data: close error on temporary file"
							, 2);
		close_fildes((*data)->infildes);
		remove_tmp("/.temp_in");
		del_fildes(&((*data)->infildes));
	}
	if ((*data)->tmp_fdout != -1)
	{
		if (close((*data)->tmp_fdout) == -1)
			ft_putendl_fd("42sh: update_data: close error on temporary file"
							, 2);
		close_fildes((*data)->outfildes);
		remove_tmp("/.temp_out");
		del_fildes(&((*data)->outfildes));
	}
//	(*data)->in_pipe = -1;
//	(*data)->out_pipe = -1;
	(*data)->tmp_fdin = -1;
	(*data)->tmp_fdout = -1;
}

t_data			*init_data(void)
{
	static t_data	*data = NULL;

	if (!data)
	{
		if (!(data = (t_data *)malloc(sizeof(t_data))))
			ft_error("init_data: memory allocation failed");
		data->error = -1;
//		data->in_pipe = -1;
//		data->out_pipe = -1;
		data->offset = 0;
		data->tmp_fdin = -1;
		data->tmp_fdout = -1;
		data->tmp_pipein = -1;
		data->tmp_pipeout = -1;
		data->infildes = NULL;
		data->outfildes = NULL;
	}
	return (data);
}

void			del_data(void)
{
	t_data	*data;

	data = init_data();
	if (data)
	{
		del_fildes(&data->infildes);
		del_fildes(&data->outfildes);
		free(data);
		data = NULL;
	}
}
