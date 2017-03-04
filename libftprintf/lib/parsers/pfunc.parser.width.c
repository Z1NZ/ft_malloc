/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.parser.width.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:14:07 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int		pfunc_parser_width(char **fmt)
{
	char		*s_number;
	char const	*p_fmt = *fmt;

	while (ft_strchr("0123456789", *p_fmt))
		p_fmt++;
	if (p_fmt > *fmt)
	{
		s_number = ft_strsub(*fmt, 0, p_fmt - *fmt);
		CONTEXT(width) = ft_atoi(s_number);
		ft_memdel((void **)&s_number);
		*fmt += p_fmt - *fmt;
		return (1);
	}
	else
		return (0);
}
