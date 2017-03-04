/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.type.x.lower.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:16:20 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

static void		pfunc_type_x_lower_precision(char **str, int check_sharp)
{
	int		len;
	char	*tmp;

	if (PREC_STATE & BITCODE)
	{
		tmp = *str;
		if (!ft_strcmp(*str, "0"))
		{
			ft_memdel((void**)&tmp);
			*str = ft_strdup("");
		}
		len = ft_strlen(*str);
		if (PRECISION > 0 && PRECISION > len)
		{
			tmp = *str;
			*str = ft_strjoin(pfunc_tool_padding('0', PRECISION - len), *str);
			ft_memdel((void**)&tmp);
			if (check_sharp)
			{
				tmp = *str;
				*str = ft_strjoin("0x", *str);
				ft_memdel((void**)&tmp);
			}
		}
	}
}

static void		pfunc_type_x_lower_width(char **str, int check_sharp)
{
	int		len;
	char	*tmp;

	if (WIDTH)
	{
		len = WIDTH - ft_strlen(*str) - ((FLAG_SHARP & BITCODE) ? 2 : 0);
		if (len > 0)
		{
			if (check_sharp && !(FLAG_ZERO & BITCODE))
			{
				tmp = *str;
				*str = ft_strjoin("0x", *str);
				ft_memdel((void**)&tmp);
			}
			tmp = *str;
			if (!(FLAG_LESS & BITCODE))
				if ((FLAG_ZERO & BITCODE) && !(PREC_STATE & BITCODE))
					*str = ft_strjoin(pfunc_tool_padding('0', len), *str);
				else
					*str = ft_strjoin(pfunc_tool_padding(' ', len), *str);
			else
				*str = ft_strjoin(*str, pfunc_tool_padding(' ', len));
			ft_memdel((void**)&tmp);
		}
	}
}

static void		pfunc_type_x_lower_casting(va_list *ap,
		unsigned long long *number)
{
	if ((MODIF_L & BITCODE) && !(MODIF_LL & BITCODE))
		*number = (unsigned long)va_arg(*ap, unsigned long);
	else if ((MODIF_L & BITCODE) && (MODIF_LL & BITCODE))
		*number = (unsigned long long)va_arg(*ap, unsigned long long);
	else if ((MODIF_H & BITCODE) && !(MODIF_HH & BITCODE))
		*number = (unsigned short)va_arg(*ap, unsigned int);
	else if ((MODIF_H & BITCODE) && (MODIF_HH & BITCODE))
		*number = (unsigned char)va_arg(*ap, unsigned int);
	else if (MODIF_J & BITCODE)
		*number = (uintmax_t)va_arg(*ap, uintmax_t);
	else if (MODIF_Z & BITCODE)
		*number = (size_t)va_arg(*ap, size_t);
	else
		*number = va_arg(*ap, unsigned int);
}

int				pfunc_type_x_lower(va_list *ap)
{
	char					*s_hexptr;
	char					*tmp;
	unsigned long long		n_hexptr;
	int						check_sharp;

	pfunc_type_x_lower_casting(ap, &n_hexptr);
	s_hexptr = pfunc_tool_dectohex(ABS(n_hexptr));
	check_sharp = ((FLAG_SHARP & BITCODE) && ft_strcmp(s_hexptr, "0"));
	pfunc_type_x_lower_precision(&s_hexptr, check_sharp);
	pfunc_type_x_lower_width(&s_hexptr, check_sharp);
	if (!ft_strstr(s_hexptr, "0x") && check_sharp)
	{
		tmp = s_hexptr;
		s_hexptr = ft_strjoin("0x", s_hexptr);
		ft_memdel((void**)&tmp);
	}
	pfunc_writer_putstr(s_hexptr);
	ft_memdel((void**)&s_hexptr);
	return (1);
}
