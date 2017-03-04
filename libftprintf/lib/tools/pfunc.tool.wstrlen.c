/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.tool.wstrlen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:15:01 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"
#include "libft.h"

int		pfunc_tool_wstrlen(wchar_t *wstring, int n)
{
	wchar_t const		*p_wstring = wstring;
	int					counter;
	int					prev;

	counter = 0;
	while (*p_wstring)
	{
		if (n >= 0)
		{
			if (counter > n)
				return (counter - prev);
		}
		prev = pfunc_tool_wcharlen(*p_wstring);
		counter += prev;
		p_wstring++;
	}
	return (counter);
}
