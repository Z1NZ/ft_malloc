/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 16:00:26 by srabah            #+#    #+#             */
/*   Updated: 2017/03/09 13:31:38 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static inline void	set_block(t_block *ptr, size_t size, int opt)
{
	ptr->size = size;
	ptr->info |= opt;
	ptr->ptr = ptr->data;
}

static inline	void	set_page(t_block *ptr, size_t size_block, int nb, int opt)
{
	int		i;
	int		len;
	t_block *new;
	t_block *tmp;

	i = 0;
	new = NULL;
	len = g_mem.page / (size_block);
	len = len * nb;
	tmp = ptr;
	len--;
	set_block(tmp, size_block, opt);
	while (i < len)
	{
		new = tmp->ptr + (size_block - SIZE_ST_HEAD);
		tmp->next = new;
		set_block(new, size_block, opt);
		tmp = tmp->next;
		i++;
	}
	tmp->next = NULL;
}


void	init_memory(size_t block_tyni, size_t block_small)
{
	unsigned int i;

	i = ROUND_UP_PAGE((TYNI_BLOCK * block_tyni), (int )g_mem.page);
	i += ROUND_UP_PAGE((SMALL_BLOCK * block_small), (int )g_mem.page);

	g_mem.main_memory = mmap(NULL, g_mem.page * i , FLAG_MALLOC, -1, 0);
	if (g_mem.main_memory == ((void *)-1))
		return  ;
	g_mem.m_tyni = (t_block *)g_mem.main_memory;
	g_mem.size_tyni = g_mem.page * (ROUND_UP_PAGE((TYNI_BLOCK * block_tyni), g_mem.page));
	set_page(g_mem.m_tyni, TYNI_BLOCK, ROUND_UP_PAGE((TYNI_BLOCK * block_tyni), g_mem.page), OPT_TYNI + OPT_BUFF);

	g_mem.m_small = (t_block *)(g_mem.main_memory + (g_mem.size_tyni));
	g_mem.size_small = g_mem.page * (ROUND_UP_PAGE((SMALL_BLOCK * block_small), g_mem.page));
	set_page(g_mem.m_small, SMALL_BLOCK, ROUND_UP_PAGE((SMALL_BLOCK * block_small), g_mem.page), OPT_SMALL + OPT_BUFF);

}