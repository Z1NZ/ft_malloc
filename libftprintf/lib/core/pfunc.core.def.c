/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.core.def.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:13:22 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		pfunc_core_def(char *fmt, va_list *ap)
{
	char		*p_fmt;

	p_fmt = fmt;
	while (*p_fmt)
	{
		if (*p_fmt == '%')
		{
			CONTEXT_RESET_DEFAULT;
			pfunc_writer_putstrn(fmt, p_fmt - fmt);
			p_fmt++;
			pfunc_parser_def(&p_fmt);
			pfunc_core_conv(ap);
			fmt = p_fmt;
		}
		else
			p_fmt++;
	}
	pfunc_writer_putstrn(fmt, p_fmt - fmt);
	return (1);
}
