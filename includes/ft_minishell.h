/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/22 13:56:53 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/04 15:50:10 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

/*
** include
*/
# include "get_next_line.h"
# include "libft.h"
# include <sys/ioctl.h>
# include <termcap.h>
# include <termios.h>

#include <stdio.h>

/*
** define
*/
# define BUILT_NUM 5
# define KEY_NUM 7
# define OPE_NUM 5

/*
** typedef
*/

typedef struct			s_built
{
	char				*name;
	void				(*apply_built)(char *);
}						t_built;

typedef struct			s_fd
{
	char				*file;
	int					fildes;
	struct s_fd			*next;
}						t_fd;

typedef struct			s_data
{
	int					error;
	int					tmp_fdin;
	int					tmp_fdout;
	int					tmp_pipein;
	int					tmp_pipeout;
	off_t				offset;
	t_fd				*infildes;
	t_fd				*outfildes;
}						t_data;

typedef struct			s_copy
{
	char				*line;
	int					index;
	int					size;
	struct s_copy		*down;
	struct s_copy		*up;
}						t_copy;

typedef struct			s_env
{
	char				**env;
	char				**path;
	char				*pwd;
	char				*oldpwd;
	char				*home;
}						t_env;

typedef struct			s_hist
{
	char				**list;
	t_copy				*copy;
}						t_hist;

typedef struct			s_id
{
	int					built;
	int					id;
	pid_t				child;
	pid_t				father;
}						t_id;

typedef struct			s_key
{
	char				*keyword;
	void				(*apply_key)(void);
}						t_key;

typedef struct			s_node
{
	char				*type;
	char				*word;
	int					pos;
	struct s_node		*left;
	struct s_node		*right;
}						t_node;

typedef struct			s_ope
{
	char				*name;
	int					prio;
}						t_ope;

typedef struct			s_proc
{
	char				*operand;
	void				(*apply_proc)(t_node *);
}						t_proc;

typedef struct stat		t_stat;

typedef struct			s_token
{
	char				*type;
	char				*word;
	int					prio;
	struct s_token		*next;
}						t_token;

/*
** global
*/
t_id					g_pid;

/*
** aff_fct.c
*/
int						aff_c(int c);
int						aff_str(char *str);

/*
** arrow_fct1.c
*/
void					apply_arrowleft(void);
void					apply_arrowright(void);
int						check_beginning(int index);
int						check_ending(int index);

/*
** arrow_fct2.c
*/
void					apply_arrowdown(void);
void					apply_arrowup(void);

/*
** built_cd.c
*/
void					apply_cd(char *command);

/*
** built_env.c
*/
void					apply_env(char *command);

/*
** built_exit.c
*/
void					apply_exit(char *command);

/*
** built_setenv.c
*/
void					apply_setenv(char *command);
int						update_var(t_env **env, char *var, char *value);

/*
** built_unsetenv.c
*/
void					apply_unsetenv(char *command);

/*
** builtins.c
*/
int						check_builtin(char *command);
void					del_builtin(void);
t_built					*init_builtin(void);

/*
** command_fct.c
*/
char					*check_command(char *command);
void					command_proc(char *command);

/*
** copy_fct.c
*/
t_copy					*add_to_copy(t_copy *copy, char *line);
t_copy					*copy_historic(char **list);
void					del_copy(t_copy **copy);

/*
** data_fct.c
*/
void					del_data(void);
t_data					*init_data(void);
void					update_data(t_data **data);

/*
** delete_fct.c
*/
void					apply_delete(void);
void					display_line(void);

/*
** edit_fct.c
*/
void					apply_edit(char c);

/*
** environ_fct.c
*/
char					**copy_env(char **environ);
char					*copy_home(char **environ);
char					*copy_oldpwd(char **environ);
char					**copy_path(char **environ);
char					*copy_pwd(char **environ);

/*
** exec_fct.c
*/
void					exec_command(char **av, int fd_out);

/*
** ft_error.c
*/
void					ft_error(char *str);

/*
** ft_errjoin.fr
*/
void					ft_errjoin(char *str1, char *str2);

/*
** ft_split.c
*/
char					**ft_split(char *str);

/*
** historic_fct.c
*/
char					**add_to_list(char **list, char *line);
t_hist					**init_historic(void);
void					del_historic(void);

/*
** lexer_fct.c
*/
char					*tokenize_other(t_token **toklist, char *line);
char					*tokenize_redir(t_token **toklist, char *line);

/*
** main.c
*/
void					del_env(void);
void					display_prompt(void);
t_env					*init_env(char **environ);

/*
** minishell.c
*/
void					del_keytab(void);
t_key					*init_keytab(void);
void					minishell(void);

/*
** operand_fct.c
*/
t_ope					check_operand(char *type);
void					del_opetab(void);
t_ope					init_operand(int prio, char *name);
t_ope					*init_opetab(void);

/*
** path_fct.c
*/
char					*build_path(char *path, char *command);
int						check_path(char *path);

/*
** parse_fct.c
*/
int						parse_toklist(t_token *toklist);

/*
** pipe_fct.c
*/
void					pipe_proc(t_node *tree);
void					update_offset(t_data **data, off_t offset);
void					write_pipefile(void);

/*
** process_fct.c
*/
void					del_proctab(void);
t_proc					*init_proctab(void);
void					read_tree(t_node *tree);

/*
** redil_fct.c
*/
void					add_infildes(t_fd **infildes, char *file, int fd);
void					redil_proc(t_node *tree);
void					write_redilfile(void);

/*
** redir_fct.c
*/
void					add_outfildes(t_fd **outfildes, char *file, int fd);
void					redir_proc(t_node *tree);
void					write_redirfile(char *file);

/*
** redirr_fct.c
*/
void					redirr_proc(t_node *tree);

/*
** return_fct.c
*/
void					apply_return(void);
int						av_size(char **av);
void					del_av(char **av);

/*
** scolon_fct.c
*/
void					scolon_proc(t_node *tree);

/*
** signal_fct.c
*/
void					catch_signal(void);
void					init_pid(void);

/*
** tempfile_fct.c
*/
void					get_tmpfd(int *tmp_fd, char *tmp_file);
void					remove_tmp(char *tmp_file);

/*
** term_fct.c
*/
void					apply_term(int set);

/*
** toklist_fct.c
*/
void					create_toklist(t_token **toklist, char *line);
void					del_toklist(t_token **toklist);
void					organize_toklist(t_node **tree, t_token **toklist,
											int pos, int prio);
/*
** tree_fct.c
*/
void					add_node(t_node **tree, t_node *elem);
void					del_tree(t_node **tree);
t_node					*new_node(char *type, char *word, int pos);
void					print_tree(t_node *tree, int i);

#endif
