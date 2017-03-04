/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.tool.dectobin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:14:23 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char			*pfunc_tool_dectobin(unsigned long long number)
{
	char		*binary;
	long long	rest;
	int			cursor;

	cursor = 0;
	binary = ft_strnew(256);
	while (number)
	{
		rest = number % 2;
		number /= 2;
		binary[cursor] = rest + '0';
		cursor++;
	}
	return (ft_strrev(binary));
}
