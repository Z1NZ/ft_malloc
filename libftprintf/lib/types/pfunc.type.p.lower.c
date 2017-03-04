/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.type.p.lower.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:15:38 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

static void		pfunc_type_p_lower_precision(char **str)
{
	int		len;
	char	*tmp;

	if (PREC_STATE & BITCODE)
	{
		if (!ft_strcmp(*str, "0"))
		{
			tmp = *str;
			*str = ft_strdup("");
			ft_memdel((void **)&tmp);
		}
		len = ft_strlen(*str);
		if (PRECISION > len)
		{
			tmp = *str;
			*str = ft_strjoin(pfunc_tool_padding('0', PRECISION - len), *str);
			ft_memdel((void **)&tmp);
			if (WIDTH - len && !(FLAG_ZERO & BITCODE) && !(FLAG_LESS & BITCODE))
			{
				tmp = *str;
				*str = ft_strjoin("0x", *str);
				ft_memdel((void **)&tmp);
			}
		}
	}
}

static void		pfunc_type_p_lower_width(char **str)
{
	int		len;
	char	*tmp;

	if (WIDTH)
	{
		len = WIDTH - ft_strlen(*str) - 2;
		if (len > 0)
		{
			tmp = *str;
			if (!(FLAG_LESS & BITCODE))
				if ((FLAG_ZERO & BITCODE) && !(PREC_STATE & BITCODE))
				{
					*str = ft_strjoin(pfunc_tool_padding('0', len), *str);
					*str = ft_strjoin("0x", *str);
				}
				else
				{
					*str = ft_strjoin("0x", *str);
					*str = ft_strjoin(pfunc_tool_padding(' ', len), *str);
				}
			else
				*str = ft_strjoin(*str, pfunc_tool_padding(' ', len));
			ft_memdel((void **)&tmp);
		}
	}
}

int				pfunc_type_p_lower(va_list *ap)
{
	char			*s_hexptr;
	unsigned long	n_hexptr;
	char			*tmp;

	n_hexptr = va_arg(*ap, unsigned long);
	s_hexptr = pfunc_tool_dectohex(ABS(n_hexptr));
	tmp = s_hexptr;
	pfunc_type_p_lower_precision(&s_hexptr);
	pfunc_type_p_lower_width(&s_hexptr);
	if (!ft_strstr(s_hexptr, "0x"))
	{
		tmp = s_hexptr;
		s_hexptr = ft_strjoin("0x", s_hexptr);
		ft_memdel((void **)&tmp);
	}
	pfunc_writer_putstr(s_hexptr);
	ft_memdel((void **)&s_hexptr);
	return (1);
}
