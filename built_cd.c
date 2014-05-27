/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/24 15:29:45 by wtrembla          #+#    #+#             */
/*   Updated: 2014/05/13 17:46:54 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <sys/stat.h>

static void		improper_path(int ret, char *path)
{
	t_stat	sb;

	lstat(path, &sb);
	if (ret == -1)
		ft_putjoin_fd("cd: no such file or directory: ", path, 2);
	else if ((sb.st_mode & S_IFMT) != S_IFDIR)
		ft_putjoin_fd("cd: not a directory: ", path, 2);
	else if (ret == -2)
		ft_putjoin_fd("cd: permission denied: ", path, 2);
}

static void		update_env(t_env **env)
{
	char	buf[2048];
	char	*new_dir;
	char	*tmp;

	ft_strdel(&(*env)->oldpwd);
	(*env)->oldpwd = (*env)->pwd;
	new_dir = ft_strdup(getcwd(buf, 2048));
	if (ft_strstr(new_dir, "/nfs/"))
		(*env)->pwd = ft_strdup(ft_strstr(new_dir, "/nfs/"));
	else
		(*env)->pwd = ft_strdup(new_dir);
	ft_strdel(&new_dir);
	if (!(update_var(env, "PWD", (*env)->pwd)))
	{
		tmp = ft_strjoin("setenv PWD ", (*env)->pwd);
		apply_setenv(tmp);
		ft_strdel(&tmp);
	}
	if (!(update_var(env, "OLDPWD", (*env)->oldpwd)))
	{
		tmp = ft_strjoin("setenv OLDPWD ", (*env)->oldpwd);
		apply_setenv(tmp);
		ft_strdel(&tmp);
	}
}

static void		go_backdir(t_env *env, char *av)
{
	int		ret;

	if (!(ret = check_path(av)) && !chdir(av))
		update_env(&env);
	if (ret)
		improper_path(ret, av);
}

static void		go_newdir(t_env *env, char *av)
{
	char	*new_dir;
	char	*tmp;
	int		ret;

	if (!ft_strncmp(av, "./", 2))
		new_dir = ft_strjoin(env->pwd, ft_strchr(av, '/'));
	else if (av[0] == '/')
		new_dir = ft_strdup(av);
	else if (!ft_strcmp(av, "-"))
		new_dir = ft_strdup(env->oldpwd);
	else
	{
		tmp = env->pwd[ft_strlen(env->pwd) - 1] != '/' ?
			ft_strjoin(env->pwd, "/") : NULL;
		new_dir = tmp != NULL ? ft_strjoin(tmp, av) : ft_strjoin(env->pwd, av);
		ft_strdel(&tmp);
	}
	if (new_dir && !(ret = check_path(new_dir)) && !chdir(new_dir))
		update_env(&env);
	if (ret)
		improper_path(ret, av);
	ft_strdel(&new_dir);
}

void			apply_cd(char *command)
{
	char	**av;
	int		size;
	t_env	*env;

	av = ft_strsplit(command, ' ');
	size = av_size(av);
	env = init_env(NULL);
	if (size > 2)
		ft_putendl_fd("cd: syntax error", 2);
	else if (size == 1 || (size == 2 && !ft_strcmp(av[1], "~")))
	{
		if (!chdir(env->home))
			update_env(&env);
	}
	else if (!ft_strncmp(av[1], "..", 2))
		go_backdir(env, av[1]);
	else
		go_newdir(env, av[1]);
	del_av(av);
}
