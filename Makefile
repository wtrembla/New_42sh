#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/13 18:51:49 by wtrembla          #+#    #+#              #
#    Updated: 2014/06/25 16:11:47 by wtrembla         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC			=	gcc
NAME		=	42sh

SRCS		=	aff_fct.c				\
				and_fct.c				\
				arrow_fct1.c			\
				arrow_fct2.c			\
				built_cd.c				\
				built_echo.c			\
				built_env.c				\
				built_exit.c			\
				built_setenv.c			\
				built_unsetenv.c		\
				builtins.c				\
				command_fct.c			\
				copy_fct.c				\
				data_fct.c				\
				delete_fct.c			\
				edit_fct.c				\
				environ_fct.c			\
				eof_fct.c				\
				exec_fct.c				\
				ft_error.c				\
				ft_split.c				\
				get_next_line.c			\
				historic_fct.c			\
				lexer_fct.c				\
				main.c					\
				minishell.c				\
				move_fct1.c				\
				move_fct2.c				\
				move_fct3.c				\
				operand_fct.c			\
				opt_cd.c				\
				opt_echo.c				\
				opt_env.c				\
				or_fct.c				\
				path_fct.c				\
				parser_fct.c			\
				pipe_fct.c				\
				process_fct.c			\
				redil_fct.c				\
				redir_fct.c				\
				redirr_fct.c			\
				return_fct.c			\
				scolon_fct.c			\
				signal_fct.c			\
				tempfile_fct.c			\
				term_fct.c				\
				toklist_fct.c			\
				tree_fct.c				\

OBJS		=	$(SRCS:.c=.o)

CFLAGS		=	-Wall -Werror -Wextra -g
HFLAGS		=	-I includes -I libft/includes
LFLAGS		=	-L libft/ -lft -ltermcap
OFLAGS		=	-O3

all:			$(NAME)

%.o:			%.c
				@$(CC) $(CFLAGS) -c $^ $(HFLAGS)

$(NAME):		libft/libft.a $(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFLAGS) $(OFLAGS)

clean:
				@make -C libft/ clean
				@rm -rf $(OBJS)

libft/libft.a:
				@make -C libft/ fclean
				@make -C libft

fclean:			clean
				@make -C libft/ fclean
				@rm -rf $(NAME)

re:				fclean all

.PHONY:			all clean re fclean
