/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.parser.flag.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:13:48 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int		pfunc_parser_flag(char **fmt)
{
	int		ret;

	ret = 0;
	while (ft_strchr("#0-+ ", **fmt))
	{
		if (**fmt == '#')
			BITCODE |= FLAG_SHARP;
		else if (**fmt == '0')
			BITCODE |= FLAG_ZERO;
		else if (**fmt == '-')
			BITCODE |= FLAG_LESS;
		else if (**fmt == '+')
			BITCODE |= FLAG_MORE;
		else if (**fmt == ' ')
			BITCODE |= FLAG_SPACE;
		(*fmt)++;
		ret++;
	}
	return (ret);
}
