/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.writer.wputchar.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:30:15 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		pfunc_writer_wputchar(wchar_t c)
{
	char	*tab_c[3];
	int		tab[3];

	tab[2] = 0;
	tab_c[1] = pfunc_tool_dectobin(c);
	tab_c[2] = pfunc_tool_unicode(tab_c[1]);
	tab[0] = pfunc_tool_countbytes(ft_strlen(tab_c[1]));
	while (tab[0]--)
	{
		tab_c[0] = ft_strsub(tab_c[2], tab[2], 8);
		tab[1] = pfunc_tool_bintodec(ft_atoi(tab_c[0]));
		ft_memdel((void **)&tab_c[0]);
		pfunc_writer_putchar(tab[1]);
		tab[2] += 8;
	}
	ft_memdel((void **)&tab_c[1]);
	ft_memdel((void **)&tab_c[2]);
	return (1);
}
