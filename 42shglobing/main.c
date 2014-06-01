/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibakayok <ibakayok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/27 17:21:48 by ibakayok          #+#    #+#             */
/*   Updated: 2014/05/27 19:31:36 by ibakayok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_glob(char *str);

int		main(int argc, char **argv)
{
	char	*str;

	if (argc != 2)
		return (-1);
	str = ft_glob(argv[1]);
	ft_printf("done\n", str);
	return (0);
}
