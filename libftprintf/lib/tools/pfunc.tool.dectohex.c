/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.tool.dectohex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:14:27 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*pfunc_tool_dectohex(unsigned long long number)
{
	char	*number_hexa;
	int		number_size;
	int		current_rest;
	int		i;

	i = 0;
	number_size = pfunc_tool_intlen(number);
	number_hexa = ft_strnew(number_size);
	while (number)
	{
		current_rest = number % 16;
		number_hexa[i] = current_rest + ((current_rest >= 10) ? 87 : '0');
		number /= 16;
		++i;
	}
	ft_strrev(number_hexa);
	if (!ft_strlen(number_hexa))
		number_hexa = ft_strdup("0");
	return (number_hexa);
}
