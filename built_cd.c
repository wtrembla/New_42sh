/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/24 15:29:45 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/17 18:44:21 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <sys/stat.h>

static void		improper_path(int ret, char *path)
{
	struct stat	sb;

	lstat(path, &sb);
	if (ret == -1)
		ft_error(ERROR(CD, E_NOEXISTENCE), path, 'n');
	else if ((sb.st_mode & S_IFMT) != S_IFDIR)
		ft_error(ERROR(CD, E_NODIR), path, 'n');
	else if (ret == -2)
		ft_error(ERROR(CD, E_NOACCES), path, 'n');
}

static void		update_env(t_env **env, char *dir)
{
	char	buf[2048];
	char	*new_dir;
	char	*tmp;

	set_option(env);
	ft_strdel(&(*env)->oldpwd);
	(*env)->oldpwd = (*env)->pwd;
	new_dir = ft_strdup(getcwd(buf, 2048));
	if ((*env)->optP == 0 && ft_strstr(new_dir, dir))
		(*env)->pwd = ft_strdup(ft_strstr(new_dir, dir));
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

static void		cd_proc(t_env *env, char *new_dir, char *av)
{
	int		ret;

	printf("new_dir = %s\n", new_dir);

	if (new_dir && !(ret = check_path(new_dir)) && !chdir(new_dir))
	{
		if (av[0] == '/')
			update_env(&env, new_dir);
		else
			update_env(&env, "/nfs");
	}
	if (ret)
	{
		improper_path(ret, av);
		g_pid.built = 0;
	}
	set_flag(&env, 0);
}

static void		go_newdir(t_env *env, char *av)
{
	char	*new_dir;
	char	*tmp;

	if (!ft_strncmp(av, "./", 2))
		new_dir = ft_strjoin(env->pwd, ft_strchr(av, '/'));
	else if (av[0] == '/')
		new_dir = ft_strdup(av);
	else if (!ft_strcmp(av, "-"))
		new_dir = ft_strdup(env->oldpwd);
	else if (!ft_strncmp(av, "..", 2))
		new_dir = ft_strdup(av);
	else
	{
		tmp = env->pwd[ft_strlen(env->pwd) - 1] != '/' ?
			ft_strjoin(env->pwd, "/") : NULL;
		new_dir = tmp != NULL ? ft_strjoin(tmp, av) : ft_strjoin(env->pwd, av);
		ft_strdel(&tmp);
	}
	cd_proc(env, new_dir, av);
	ft_strdel(&new_dir);
}

void			apply_cd(char *command)
{
	char	**av;
	int		size;
	t_env	*env;

	av = ft_strsplit(command, ' ');
	size = av_size(av);
	env = init_env(NULL, 0);
	if (!parse_cd(av))
	{
		if (size == 1 || (size == 2 && !ft_strcmp(av[1], "-P"))
			|| (size == 2 && !ft_strcmp(av[1], "-L"))
			|| (size == 2 && !ft_strcmp(av[1], "~"))
			|| (size == 3 && !ft_strcmp(av[2], "~")))
		{
			if (!chdir(env->home))
				update_env(&env, "/nfs");
			set_flag(&env, 0);
		}
		else
			go_newdir(env, av[size - 1]);
		if (g_pid.built == -1)
			g_pid.built = 1;
	}
	del_av(av);
}
