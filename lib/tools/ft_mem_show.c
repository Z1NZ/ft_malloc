/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_show.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 20:05:27 by srabah            #+#    #+#             */
/*   Updated: 2017/03/14 20:05:51 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			pri_addr(unsigned long long number)
{
	static char	base[] = "0123456789abcdef";
	int			current_rest;
	char		addr[16];
	int			i;

	current_rest = 0;
	i = 0;
	while (number)
	{
		current_rest = number % 16;
		addr[i] = base[current_rest];
		number /= 16;
		i++;
	}
	i--;
	while (i > -1)
	{
		write(1, &addr[i], 1);
		i--;
	}
}

void			show_list(t_block *tmp, char *name)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (tmp)
	{
		if (CHECK_BIT(tmp->info, OPT_MAP_HEAD))
			i = 0;
		ft_putstr(name);
		ft_putstr(RED" pos = [");
		ft_putnbr(j);
		ft_putstr("][");
		ft_putnbr(i);
		ft_putstr("]"GRN" addr = [0x");
		pri_addr((unsigned long long)tmp);
		ft_putstr("]"CYN" size = [");
		ft_putnbr((int)(tmp->size));
		ft_putstr("]"RESET" info = [");
		ft_putnbr(tmp->info);
		ft_putstr("]\n");
		tmp = tmp->next;
		j++;
		i++;
	}
}

static void		show_list_simple(t_block *tmp, char *name)
{
	ft_putstr(name);
	ft_putstr(":\n");
	while (tmp)
	{
		write(1, "0x", 2);
		pri_addr((unsigned long long)tmp);
		ft_putstr(" - ");
		write(1, "0x", 2);
		pri_addr((unsigned long long)tmp + (tmp->size));
		ft_putstr(" : ");
		ft_putnbr((int)(tmp->size));
		ft_putstr("\n");
		tmp = tmp->next;
	}
}

void			show_alloc_mem(void)
{
	if (pthread_mutex_lock(&(g_mem.mutex_show)) == EINVAL)
	{
		pthread_mutex_init(&(g_mem.mutex_show), NULL);
		pthread_mutex_lock(&(g_mem.mutex_show));
	}
	show_list_simple(g_mem.m_tyni, "TYNI");
	show_list_simple(g_mem.m_small, "SMALL");
	show_list_simple(g_mem.m_large, "LARGE");
	pthread_mutex_unlock(&(g_mem.mutex_show));
}

void			show_alloc_mem_ex(void)
{
	if (pthread_mutex_lock(&(g_mem.mutex_show_ex)) == EINVAL)
	{
		pthread_mutex_init(&(g_mem.mutex_show_ex), NULL);
		pthread_mutex_lock(&(g_mem.mutex_show_ex));
	}
	show_list(g_mem.m_tyni, "TYNI");
	show_list(g_mem.m_small, "SMALL");
	show_list(g_mem.m_large, "LARGE");
	pthread_mutex_unlock(&(g_mem.mutex_show_ex));
}
