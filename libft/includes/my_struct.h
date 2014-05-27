/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/18 20:44:18 by wtrembla          #+#    #+#             */
/*   Updated: 2014/04/18 20:45:46 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_STRUCT_H
# define MY_STRUCT_H

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

#endif
