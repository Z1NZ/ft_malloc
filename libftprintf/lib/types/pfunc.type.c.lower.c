/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.type.c.lower.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:15:10 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

static void		pfunc_type_c_lower_width_padding(int len)
{
	char	*tmp;

	if ((FLAG_ZERO & BITCODE))
	{
		tmp = pfunc_tool_padding('0', len);
		pfunc_writer_putstr(tmp);
		ft_memdel((void **)&tmp);
	}
	else
	{
		tmp = pfunc_tool_padding(' ', len);
		pfunc_writer_putstr(tmp);
		ft_memdel((void **)&tmp);
	}
}

static void		pfunc_type_c_lower_width(void)
{
	int		len;

	if (WIDTH)
	{
		len = WIDTH - 1;
		if (len > 0)
		{
			if (!(FLAG_LESS & BITCODE))
				pfunc_type_c_lower_width_padding(len);
			else
				pfunc_type_c_lower_width_padding(len);
		}
	}
}

int				pfunc_type_c_lower(va_list *ap)
{
	char		c_char;

	if (MODIF_L & BITCODE)
		pfunc_type_c_upper(ap);
	else
	{
		c_char = (char)va_arg(*ap, int);
		if (!(FLAG_LESS & BITCODE))
			pfunc_type_c_lower_width();
		pfunc_writer_putchar(c_char);
		if (FLAG_LESS & BITCODE)
			pfunc_type_c_lower_width();
	}
	return (1);
}
