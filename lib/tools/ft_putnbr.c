/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 23:28:40 by srabah            #+#    #+#             */
/*   Updated: 2017/05/06 23:28:44 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			ft_putnbr(int n)
{
	unsigned int	count;
	unsigned int	u_nbr;

	count = 0;
	u_nbr = n;
	if (n < 0)
	{
		ft_putchar('-');
		u_nbr = -n;
	}
	if (u_nbr / 10)
		ft_putnbr(u_nbr / 10);
	ft_putchar(u_nbr % 10 + '0');
}
