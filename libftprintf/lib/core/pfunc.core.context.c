/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.core.context.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:13:11 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

t_context	*pfunc_core_context_init(void)
{
	static t_context	*context = NULL;

	if (!context)
	{
		context = malloc(sizeof(t_context));
		CONTEXT_RESET_FLUSH;
	}
	return (context);
}

int			pfunc_core_context_reset(int flush)
{
	if (!flush)
		CONTEXT(ret) = 0;
	CONTEXT(bitcode) = 0;
	CONTEXT(width) = 0;
	CONTEXT(precision) = 0;
	CONTEXT(conversion) = 0;
	return (1);
}
