/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.tool.usigner.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:14:50 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static char		*pfunc_tool_usigner_process(int check, char *conv)
{
	char	*number_signed;
	char	*p_number_signed;
	char	*match;

	number_signed = ft_strnew(ft_strlen(conv) + 1);
	p_number_signed = number_signed;
	match = conv;
	while (*match == ' ')
	{
		*number_signed = *conv;
		match++;
		number_signed++;
	}
	if (check && check % 16)
		*number_signed = '-';
	else
		*number_signed = '+';
	number_signed++;
	while (*match)
		*number_signed++ = *match++;
	return (p_number_signed);
}

char			*pfunc_tool_usigner(char *conv, unsigned long long number)
{
	int		check;

	(void)number;
	if (!conv)
		return (NULL);
	check = FLAG_MORE & BITCODE;
	if (check > 0)
		return (pfunc_tool_usigner_process(check, conv));
	else
		return (conv);
}
