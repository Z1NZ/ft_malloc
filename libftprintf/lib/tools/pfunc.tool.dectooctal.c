/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.tool.dectooctal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:14:30 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char		*pfunc_tool_dectooctal(unsigned long long number)
{
	long long		number_octal;
	long long		current_rest;
	int				i;
	char			*octal;

	octal = ft_strnew(256);
	i = 0;
	number_octal = 0;
	if (!number)
		octal[i] = '0';
	while (number != 0)
	{
		current_rest = number % 8;
		number /= 8;
		octal[i] = current_rest + '0';
		i++;
	}
	ft_strrev(octal);
	return (octal);
}
