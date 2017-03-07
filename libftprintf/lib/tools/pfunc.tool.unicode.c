/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.tool.unicode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:32:01 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

static char		**pfunc_tool_unicode_tabinit(void)
{
	char	**tab;
	
	tab = (char **)mmap(NULL, (sizeof(char *) * 5), FLAG_MALLOC, -1, 0);
	tab[0] = ft_strdup("0xxxxxxx");
	tab[1] = ft_strdup("110xxxxx10xxxxxx");
	tab[2] = ft_strdup("1110xxxx10xxxxxx10xxxxxx");
	tab[3] = ft_strdup("11110xxx10xxxxxx10xxxxxx10xxxxxx");
	return (tab);
}

static void		pfunc_tool_unicode_transform(char *cur_mask, char *wchar,
					char *binary)
{
	while (*cur_mask)
	{
		if (*cur_mask == 'x')
		{
			if (*binary)
			{
				*wchar = *binary;
				binary++;
			}
			else
				*wchar = '0';
		}
		else
			*wchar = *cur_mask;
		wchar++;
		cur_mask++;
	}
}

char			*pfunc_tool_unicode(char *binary)
{
	char	**tab;
	char	*cur_mask;
	char	*wchar;
	char	*wchar_begin;
	int		choice;

	choice = 0;
	tab = pfunc_tool_unicode_tabinit();
	choice = pfunc_tool_countbytes(ft_strlen(binary)) - 1;
	wchar = ft_strnew(ft_strlen(tab[choice]));
	wchar_begin = wchar;
	ft_strrev(tab[choice]);
	cur_mask = tab[choice];
	ft_strrev(binary);
	pfunc_tool_unicode_transform(cur_mask, wchar, binary);
	ft_memdel((void **)&tab[0]);
	ft_memdel((void **)&tab[1]);
	ft_memdel((void **)&tab[2]);
	ft_memdel((void **)&tab[3]);
	ft_memdel((void **)&tab);
	return (ft_strrev(wchar_begin));
}
