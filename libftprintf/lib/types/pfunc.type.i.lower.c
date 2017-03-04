/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.type.i.lower.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:39:09 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

static void		pfunc_type_i_lower_width_padding(int len, char **str)
{
	char	*tmp;

	if (!(FLAG_LESS & BITCODE))
		if ((FLAG_ZERO & BITCODE) && !(PREC_STATE & BITCODE))
		{
			tmp = pfunc_tool_padding('0', len);
			*str = ft_strjoin(tmp, *str);
			ft_memdel((void **)&tmp);
		}
		else
		{
			tmp = pfunc_tool_padding(' ', len);
			*str = ft_strjoin(tmp, *str);
			ft_memdel((void **)&tmp);
		}
	else
	{
		tmp = pfunc_tool_padding(' ', len);
		*str = ft_strjoin(*str, tmp);
		ft_memdel((void **)&tmp);
	}
}

static void		pfunc_type_i_lower_precision(long long number, char **s_number)
{
	int		n_len;
	char	*tmp;
	char	*tmp1;

	tmp = *s_number;
	n_len = pfunc_tool_intlen(ABS(number));
	if (PREC_STATE & BITCODE)
	{
		if (PRECISION > n_len)
		{
			tmp1 = pfunc_tool_padding('0', PRECISION - n_len);
			*s_number = ft_strjoin(tmp1, *s_number);
			ft_memdel((void **)&tmp1);
		}
		else if (PRECISION == 0 && number == 0)
			*s_number = ft_strdup("\0");
	}
	if (tmp != *s_number)
		ft_memdel((void **)&tmp);
}

static void		pfunc_type_i_lower_width(long long number, char **str)
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
			pfunc_type_i_lower_width_padding(len, str);
			ft_memdel((void **)&tmp);
		}
	}
	if ((FLAG_SPACE & BITCODE) && !(FLAG_MORE & BITCODE) && number >= 0)
	{
		tmp = *str;
		*str = ft_strjoin(" ", *str);
		ft_memdel((void **)&tmp);
	}
}

static void		pfunc_type_i_lower_casting(va_list *ap, long long *number)
{
	if ((MODIF_L & BITCODE) && !(MODIF_LL & BITCODE))
		*number = (long)va_arg(*ap, long);
	else if ((MODIF_L & BITCODE) && (MODIF_LL & BITCODE))
		*number = (long long)va_arg(*ap, long long);
	else if ((MODIF_H & BITCODE) && !(MODIF_HH & BITCODE))
		*number = (short)va_arg(*ap, int);
	else if ((MODIF_H & BITCODE) && (MODIF_HH & BITCODE))
	{
		*number = (signed char)va_arg(*ap, int);
	}
	else if (MODIF_J & BITCODE)
		*number = (intmax_t)va_arg(*ap, intmax_t);
	else if (MODIF_Z & BITCODE)
		*number = (size_t)va_arg(*ap, size_t);
	else
		*number = va_arg(*ap, int);
}

int				pfunc_type_i_lower(va_list *ap)
{
	long long	number;
	char		*s_number;

	number = 0;
	pfunc_type_i_lower_casting(ap, &number);
	s_number = pfunc_tool_itoa(ABS(number));
	pfunc_type_i_lower_precision(number, &s_number);
	pfunc_type_i_lower_width(number, &s_number);
	s_number = pfunc_tool_signer(s_number, number);
	pfunc_writer_putstr(s_number);
	return (0);
}
