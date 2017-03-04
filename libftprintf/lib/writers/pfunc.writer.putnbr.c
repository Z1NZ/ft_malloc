/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.writer.putnbr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:30:07 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

static int		pfunc_writer_putnbr_process(long long n)
{
	unsigned long long	nb;

	nb = n;
	if (n < 0)
	{
		pfunc_writer_putchar('-');
		nb = -n;
	}
	if (nb >= 10)
	{
		pfunc_writer_putnbr(nb / 10);
		pfunc_writer_putnbr(nb % 10);
	}
	if (nb < 10)
		pfunc_writer_putchar(nb + 48);
	return (1);
}

int				pfunc_writer_putnbr(long long n)
{
	long long	number;

	number = pfunc_writer_putnbr_process(n);
	if (number < 0)
		CONTEXT(ret) += 1;
	CONTEXT(ret) += pfunc_tool_intlen(ABS(number));
	return (1);
}
