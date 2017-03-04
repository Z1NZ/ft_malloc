/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.parser.precision.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:13:59 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static	int		pfunc_parser_precision_state(void)
{
	PRECISION = 0;
	BITCODE |= PREC_STATE;
	return (1);
}

int				pfunc_parser_precision(char **fmt)
{
	int			precision;
	char		*s_number;
	char const	*p_fmt = *fmt;

	precision = 0;
	if (*p_fmt == '.')
	{
		precision++;
		(*fmt)++;
		p_fmt++;
		while (ft_strchr("0123456789", *p_fmt))
			p_fmt++;
	}
	if (p_fmt - *fmt > 0)
	{
		s_number = ft_strsub(*fmt, 0, p_fmt - *fmt);
		PRECISION = ft_atoi(s_number);
		ft_memdel((void **)&s_number);
		BITCODE |= PREC_STATE;
		*fmt += p_fmt - *fmt;
		return (1);
	}
	else if (precision)
		return (pfunc_parser_precision_state());
	return (0);
}
