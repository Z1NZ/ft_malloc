/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.type.percent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:15:41 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

static void		pfunc_type_percent_width(void)
{
	int		len;

	if (WIDTH)
	{
		len = WIDTH - 1;
		if (len > 0)
		{
			if ((FLAG_ZERO & BITCODE))
				pfunc_writer_putstr(pfunc_tool_padding('0', len));
			else
				pfunc_writer_putstr(pfunc_tool_padding(' ', len));
		}
	}
}

static void		pfunc_type_percent_width_back(void)
{
	int		len;

	if (WIDTH)
	{
		len = WIDTH - 1;
		if (len > 0)
		{
			if ((FLAG_ZERO & BITCODE))
				pfunc_writer_putstr(pfunc_tool_padding(' ', len));
			else
				pfunc_writer_putstr(pfunc_tool_padding(' ', len));
		}
	}
}

int				pfunc_type_percent(va_list *ap)
{
	(void)ap;
	if (!(FLAG_LESS & BITCODE))
		pfunc_type_percent_width();
	pfunc_writer_putchar('%');
	if (FLAG_LESS & BITCODE)
		pfunc_type_percent_width_back();
	return (0);
}
