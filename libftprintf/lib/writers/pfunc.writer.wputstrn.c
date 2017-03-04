/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.writer.wputstrn.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:30:22 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static int		pfunc_writer_wputstrn_at(wchar_t c, int *steps)
{
	char	*binary;
	char	*wchar;
	int		bytes_number;
	int		decimal;
	int		start;

	start = 0;
	binary = pfunc_tool_dectobin(c);
	wchar = pfunc_tool_unicode(binary);
	bytes_number = pfunc_tool_countbytes(ft_strlen(binary));
	if (*steps >= bytes_number)
	{
		*steps -= bytes_number;
		while (bytes_number--)
		{
			decimal = pfunc_tool_bintodec(ft_atoi(ft_strsub(wchar, start, 8)));
			pfunc_writer_putchar(decimal);
			start += 8;
		}
	}
	if (*steps <= 0)
		return (*steps);
	else
		return (1);
}

void			pfunc_writer_wputstrn(wchar_t *wstring, int n)
{
	int		steps;

	steps = n;
	while (*wstring)
	{
		if (pfunc_writer_wputstrn_at(*wstring, &steps) <= 0)
			break ;
		wstring++;
	}
	PRECISION += -(steps);
}
