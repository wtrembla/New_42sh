/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 18:19:42 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/25 14:58:04 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define EXPAND(A, B) # A # B
# define ERROR(A, B) EXPAND(A, B)
# define SH 42sh:\040
# define CD cd:\040
# define ENV env:\040
# define EXIT exit:\040
# define SETENV setenv:\040
# define UNSETENV unsetenv:\040
# define E_CALLSYS call system error:\040
# define E_CLOSE close error:\040
# define E_CREATETMP temporary file not created\n
# define E_ILLEGALOPT illegal option --\040
# define E_IMPENV improper environment\n
# define E_ISDIR is a directory:\040
# define E_FEWARGS too few arguments\n
# define E_MANYARGS too many arguments\n
# define E_MEMALLOC memory allocation failed\040
# define E_NOACCESS permission denied:\040
# define E_NOCMD command not found:\040
# define E_NODIR not a directory:\040
# define E_NOEXISTENCE no such file or directory:\040
# define E_OPEN open error:\040
# define E_PARSE parse error near: `
# define E_RMTMP temporary file not removed\n
# define E_SYNTAX syntax error\n

#endif
