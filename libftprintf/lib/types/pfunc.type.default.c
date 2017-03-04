/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.type.default.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:15:26 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void		pfunc_type_default_width_padding(int len)
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

static void		pfunc_type_default_width(void)
{
	int		len;

	if (WIDTH)
	{
		len = WIDTH - 1;
		if (len > 0)
		{
			if (!(FLAG_LESS & BITCODE))
				pfunc_type_default_width_padding(len);
			else
				pfunc_type_default_width_padding(len);
		}
	}
}

int				pfunc_type_default(va_list *ap)
{
	(void)ap;
	if (!(FLAG_LESS & BITCODE))
		pfunc_type_default_width();
	if (CONVERSION && C_IS_UNKNOWN)
		pfunc_writer_putchar(CONVERSION);
	if (FLAG_LESS & BITCODE)
		pfunc_type_default_width();
	return (0);
}
