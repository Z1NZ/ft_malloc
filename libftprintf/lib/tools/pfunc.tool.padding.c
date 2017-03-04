/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.tool.padding.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:14:39 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "ft_printf.h"

char		*pfunc_tool_padding(char padder, size_t len)
{
	char			*padding;
	size_t			i;

	padding = ft_strnew(len);
	i = 0;
	if (padder)
	{
		while (i < len)
		{
			padding[i] = padder;
			i++;
		}
		return (padding);
	}
	return (NULL);
}
