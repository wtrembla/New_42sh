#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/13 18:51:49 by wtrembla          #+#    #+#              #
#    Updated: 2014/05/27 14:33:47 by wtrembla         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC			=	gcc
NAME		=	ft_minishell2

SRCS		=	built_cd.c				\
				built_env.c				\
				built_exit.c			\
				built_setenv.c			\
				built_unsetenv.c		\
				builtins.c				\
				command_fct.c			\
				data_fct.c				\
				environ_fct.c			\
				exec_fct.c				\
				ft_error.c				\
				ft_errjoin.c			\
				ft_split.c				\
				get_next_line.c			\
				lexer_fct.c				\
				main.c					\
				minishell.c				\
				operand_fct.c			\
				path_fct.c				\
				parse_fct.c				\
				pipe_fct.c				\
				process_fct.c			\
				redil_fct.c				\
				redir_fct.c				\
				redirr_fct.c			\
				scolon_fct.c			\
				signal_fct.c			\
				tempfile_fct.c			\
				toklist_fct.c			\
				tree_fct.c				\

OBJS		=	$(SRCS:.c=.o)

CFLAGS		=	-Wall -Werror -Wextra -g
HFLAGS		=	-I includes -I libft/includes
LFLAGS		=	-L libft/ -lft
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
