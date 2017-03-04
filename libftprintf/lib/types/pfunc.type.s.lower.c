/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.type.s.lower.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:39:23 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

static void		pfunc_type_s_lower_precision(char **str)
{
	char	*tmp_str;

	if (PREC_STATE & BITCODE)
	{
		if (ft_strlen(*str) > (size_t)PRECISION)
		{
			tmp_str = *str;
			*str = ft_strsub(*str, 0, PRECISION);
		}
	}
}

static void		pfunc_type_s_lower_width(char **str)
{
	int		len;

	if (WIDTH)
	{
		len = WIDTH - ft_strlen(*str);
		if (len > 0)
		{
			if (!(FLAG_LESS & BITCODE))
			{
				if (FLAG_ZERO & BITCODE)
					*str = ft_strjoin(pfunc_tool_padding('0', len), *str);
				else
					*str = ft_strjoin(pfunc_tool_padding(' ', len), *str);
			}
			else
				*str = ft_strjoin(*str, pfunc_tool_padding(' ', len));
		}
	}
}

int				pfunc_type_s_lower(va_list *ap)
{
	char	*str;

	str = NULL;
	if (MODIF_L & BITCODE)
		pfunc_type_s_upper(ap);
	else
	{
		if (ap)
			str = va_arg(*ap, char *);
		if (!str)
			str = ft_strdup("(null)");
		else
			str = ft_strdup(str);
		pfunc_type_s_lower_precision(&str);
		pfunc_type_s_lower_width(&str);
		pfunc_writer_putstr(str);
		ft_memdel((void**)&str);
	}
	return (0);
}
