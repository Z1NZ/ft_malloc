/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.parser.type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:14:03 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int		pfunc_parser_type(char **fmt)
{
	if (ft_strchr("sSpdDioOuUxXcC%", **fmt))
	{
		CONTEXT(conversion) = **fmt;
		(*fmt)++;
		return (1);
	}
	else if (!ft_strchr("0123456789 .#-+hljz%", **fmt) && **fmt)
	{
		CONTEXT(conversion) = **fmt;
		(*fmt)++;
		return (1);
	}
	else
		return (0);
}
