/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/15 20:51:58 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/06 20:26:06 by wtrembla         ###   ########.fr       */
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
				ft_error(ERROR(SH, E_CLOSE), tmp->file, 'n');
			tmp = tmp->next;
		}
	}
}

void			update_data(t_data **data)
{
	if ((*data)->tmp_fdin != -1)
	{
		if (close((*data)->tmp_fdin) == -1)
			ft_error(ERROR(SH, E_CLOSE), "temporary infile", 'n');
		close_fildes((*data)->infildes);
		remove_tmp("/.temp_in");
		del_fildes(&((*data)->infildes));
	}
	if ((*data)->tmp_fdout != -1)
	{
		if (close((*data)->tmp_fdout) == -1)
			ft_error(ERROR(SH, E_CLOSE), "temporary outfile", 'n');
		close_fildes((*data)->outfildes);
		remove_tmp("/.temp_out");
		del_fildes(&((*data)->outfildes));
	}
	(*data)->tmp_fdin = -1;
	(*data)->tmp_fdout = -1;
}

t_data			*init_data(int set)
{
	static t_data	*data = NULL;

	if (!data && set == 1)
	{
		if (!(data = (t_data *)malloc(sizeof(t_data))))
			ft_error(ERROR(SH, E_MEMALLOC), "(initializing data)", 'y');
		data->error = -1;
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

	data = init_data(0);
	if (data)
	{
		del_fildes(&data->infildes);
		del_fildes(&data->outfildes);
		free(data);
		data = NULL;
	}
}
