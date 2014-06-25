/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/15 20:01:14 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/25 17:12:05 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "ft_minishell.h"
#include <sys/stat.h>

static int		check_file(char *file)
{
	int				fd;
	struct stat		sb;

	fd = -1;
	lstat(file, &sb);
	if (!access(file, F_OK) && (sb.st_mode & S_IFMT) == S_IFDIR)
		ft_error(ERROR(SH, E_ISDIR), file, 'n');
	else if (!access(file, F_OK) && access(file, W_OK) == -1)
		ft_error(ERROR(SH, E_NOACCESS), file, 'n');
	else if ((fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		ft_error(ERROR(SH, E_OPEN), file, 'n');
	return (fd);
}

void			write_redirfile(void)
{
	char	*line;
	t_data	*data;
	t_fd	*tmp;

	data = init_data(0);
	tmp = data->outfildes;
	while (tmp)
	{
		lseek(data->tmp_fdout, 0, SEEK_SET);
		while (get_next_line(data->tmp_fdout, &line) > 0)
		{
			ft_putendl_fd(line, tmp->fildes);
			ft_strdel(&line);
		}
		tmp = tmp->next;
	}
}

void			add_outfildes(t_fd **outfildes, char *file, int fd)
{
	t_fd	*elem;
	t_fd	*tmp;

	if (!(elem = (t_fd *)malloc(sizeof(t_fd))))
		ft_error(ERROR(SH, E_MEMALLOC), "(adding outfile)", 'n');
	else
	{
		elem->file = ft_strdup(file);
		elem->fildes = fd;
		elem->next = NULL;
		tmp = *outfildes;
		if (*outfildes)
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = elem;
		}
		else
			*outfildes = elem;
	}
}

void			redir_proc(t_node *tree)
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
