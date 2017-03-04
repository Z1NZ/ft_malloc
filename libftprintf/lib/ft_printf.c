/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:16:54 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

int		ft_printf(char *fmt, ...)
{
	va_list		ap;
	int			ret;

	CONTEXT_RESET_FLUSH;
	va_start(ap, fmt);
	if (!fmt)
		return (0);
	ret = pfunc_core_def(fmt, &ap);
	va_end(ap);
	return (CONTEXT(ret));
}
