/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.parser.def.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:13:42 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		pfunc_parser_def(char **fmt)
{
	int		ret;

	ret = 0;
	while (!(ret += pfunc_parser_type(fmt)))
	{
		ret += pfunc_parser_flag(fmt);
		ret += pfunc_parser_width(fmt);
		ret += pfunc_parser_precision(fmt);
		ret += pfunc_parser_modifier(fmt);
		if (!ret)
			return (0);
		else
			ret = 0;
	}
	return (1);
}
