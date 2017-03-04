/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.type.u.lower.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:16:12 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

static void	pfunc_type_u_lower_precision(long long number, char **s_number)
{
	int		n_len;
	char	*tmp;

	tmp = *s_number;
	n_len = pfunc_tool_intlen(ABS(number));
	if (PREC_STATE & BITCODE)
	{
		if (PRECISION > n_len)
		{
			*s_number = ft_strjoin(pfunc_tool_padding('0', PRECISION - n_len),
				*s_number);
		}
		else if (PRECISION == 0 && number == 0)
			*s_number = ft_strdup("\0");
	}
	if (tmp != *s_number)
		ft_memdel((void **)&tmp);
}

static void	pfunc_type_u_lower_width(long long number, char **str)
{
	int		len;
	char	*tmp;

	if (WIDTH)
	{
		len = WIDTH - ft_strlen(*str);
		(number < 0 || FLAG_MORE & BITCODE || (FLAG_SPACE & BITCODE))
			? len-- : ' ';
		if (len > 0)
		{
			tmp = *str;
			if (!(FLAG_LESS & BITCODE))
			{
				if ((FLAG_ZERO & BITCODE) && !(PREC_STATE & BITCODE))
					*str = ft_strjoin(pfunc_tool_padding('0', len), *str);
				else
					*str = ft_strjoin(pfunc_tool_padding(' ', len), *str);
			}
			else
				*str = ft_strjoin(*str, pfunc_tool_padding(' ', len));
			ft_memdel((void **)&tmp);
		}
	}
}

static void	pfunc_type_u_lower_casting(va_list *ap, unsigned long long *number)
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

int			pfunc_type_u_lower(va_list *ap)
{
	unsigned long long	number;
	char				*s_number;

	number = 0;
	pfunc_type_u_lower_casting(ap, &number);
	s_number = pfunc_tool_itoa(ABS(number));
	pfunc_type_u_lower_precision(number, &s_number);
	pfunc_type_u_lower_width(number, &s_number);
	pfunc_writer_putstr(s_number);
	ft_memdel((void **)&s_number);
	return (0);
}
