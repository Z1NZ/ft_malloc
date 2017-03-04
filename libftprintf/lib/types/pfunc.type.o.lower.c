/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.type.o.lower.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:15:31 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

static void	pfunc_type_o_lower_precision(char **str, unsigned long long number)
{
	int		len;
	char	*tmp;

	if (PREC_STATE & BITCODE)
	{
		tmp = *str;
		len = ft_strlen(*str);
		if (PRECISION > len && PRECISION > 0)
			*str = ft_strjoin(pfunc_tool_padding('0', PRECISION - len), *str);
		else if (PRECISION == 0 && !number && !(FLAG_SHARP & BITCODE))
			*str = ft_strdup("");
		if (tmp != *str)
			ft_memdel((void **)&tmp);
	}
}

static void	pfunc_type_o_lower_width(char **str)
{
	int		len;
	char	*tmp;

	if (WIDTH)
	{
		len = WIDTH - ft_strlen(*str);
		if (len > 0)
		{
			tmp = *str;
			if (!(FLAG_LESS & BITCODE))
			{
				if ((FLAG_ZERO & BITCODE) && !(PREC_STATE & BITCODE))
				{
					*str = ft_strjoin(pfunc_tool_padding('0', len), *str);
				}
				else
					*str = ft_strjoin(pfunc_tool_padding(' ', len), *str);
			}
			else
				*str = ft_strjoin(*str, pfunc_tool_padding(' ', len));
			ft_memdel((void **)&tmp);
		}
	}
}

static void	pfunc_type_o_lower_casting(va_list *ap, unsigned long long *number)
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

int			pfunc_type_o_lower(va_list *ap)
{
	char				*s_octptr;
	unsigned long long	n_octptr;
	char				*tmp;

	pfunc_type_o_lower_casting(ap, &n_octptr);
	s_octptr = pfunc_tool_dectooctal(ABS(n_octptr));
	if ((FLAG_SHARP & BITCODE) && n_octptr)
	{
		tmp = s_octptr;
		s_octptr = ft_strjoin("0", s_octptr);
		ft_memdel((void **)&tmp);
	}
	pfunc_type_o_lower_precision(&s_octptr, n_octptr);
	pfunc_type_o_lower_width(&s_octptr);
	pfunc_writer_putstr(s_octptr);
	ft_memdel((void **)&s_octptr);
	return (1);
}
