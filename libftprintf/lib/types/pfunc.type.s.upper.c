/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.type.s.upper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:15:49 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <wchar.h>
#include "libft.h"
#include "ft_printf.h"

static void		pfunc_type_s_upper_width_padding(int len)
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

static void		pfunc_type_s_upper_width(wchar_t *wstring)
{
	int		len;
	char	*tmp;

	if (WIDTH)
	{
		if ((PREC_STATE & BITCODE) &&
			PRECISION < pfunc_tool_wstrlen(wstring, -1))
		{
			len = WIDTH - pfunc_tool_wstrlen(wstring, PRECISION);
		}
		else
			len = WIDTH - pfunc_tool_wstrlen(wstring, -1);
		if (len > 0)
		{
			if (!(FLAG_LESS & BITCODE))
				pfunc_type_s_upper_width_padding(len);
			else
			{
				tmp = pfunc_tool_padding(' ', len);
				pfunc_writer_putstr(tmp);
				ft_memdel((void **)&tmp);
			}
		}
	}
}

int				pfunc_type_s_upper(va_list *ap)
{
	wchar_t		*wstring;

	wstring = va_arg(*ap, wchar_t *);
	if (!wstring)
		pfunc_type_s_lower(NULL);
	else
	{
		if (!(FLAG_LESS & BITCODE))
			pfunc_type_s_upper_width(wstring);
		if (PREC_STATE & BITCODE && PRECISION < pfunc_tool_wstrlen(wstring, -1))
			pfunc_writer_wputstrn(wstring, PRECISION);
		else
			pfunc_writer_wputstr(wstring);
		if (FLAG_LESS & BITCODE)
			pfunc_type_s_upper_width(wstring);
	}
	return (1);
}
