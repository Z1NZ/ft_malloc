/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_small.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:21:17 by srabah            #+#    #+#             */
/*   Updated: 2017/02/15 16:26:22 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static inline void	set_block(t_block *ptr, size_t size, int on)
{
	ptr->size = size;
	if (on)
		ptr->info |= OPT_FREE;
	ptr->ptr = ptr->data;
	if (on)
		g_mem.use_small += size;
}

static inline void	set_page(t_block *ptr, size_t size_block)
{
	int		i;
	int		len;
	t_block *new;
	t_block *tmp;

	i = 1;
	new = NULL;
	len = g_mem.page / (size_block);
	tmp = ptr;
	while (i < len)
	{
		new = tmp->ptr + (size_block - SIZE_ST_HEAD);
		tmp->next = new;
		set_block(new, size_block, 0);
		tmp = tmp->next;
		i++;
	}
	tmp->next = NULL;
}

static void			*add_page(void)
{
	t_block		*ptr;
	t_block		*tmp;

	ptr = (t_block *)mmap(NULL, g_mem.page, FLAG_MALLOC, -1, 0);
	if (ptr == ((void *)-1))
		return (NULL);
	g_mem.size_small += g_mem.page;
	tmp = g_mem.m_small;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ptr;
	ptr->info |= OPT_MAP_HEAD;
	set_block(ptr, SMALL_BLOCK, 0);
	ptr->next = NULL;
	set_page(ptr, SMALL_BLOCK);
	return (ptr);
}

static int			init_small_page(void)
{
	t_block *ptr;

	g_mem.size_small = g_mem.page;
	ptr = (t_block *)mmap(NULL, g_mem.page, FLAG_MALLOC, -1, 0);
	if (ptr == ((void *)-1))
		return (1);
	ptr->size = SMALL_BLOCK;
	ptr->info |= OPT_MAP_HEAD;
	set_block(ptr, SMALL_BLOCK, 0);
	ptr->next = NULL;
	g_mem.m_small = ptr;
	set_page(ptr, SMALL_BLOCK);
	return (0);
}

void				*alloc_small(size_t size)
{
	t_block *ptr;

	ptr = NULL;
	if (g_mem.size_small == 0)
	{
		if (init_small_page() == 1)
			return (NULL);
	}
	if ((g_mem.size_small - g_mem.use_small) >= SMALL_BLOCK * size)
		ptr = find_fusion_location(g_mem.m_small, size);
	else
		ptr = add_page();
	if (ptr != ((void *)-1))
		set_block(ptr, SMALL_BLOCK * size, OPT_FREE);
	pthread_mutex_unlock(&(g_mem.mutex));
	return ((((ptr != ((void *)-1)) || ptr) ? ptr->data : NULL));
}
