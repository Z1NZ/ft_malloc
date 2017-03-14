/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_large.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 08:44:38 by srabah            #+#    #+#             */
/*   Updated: 2017/03/14 21:01:42 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block		*add_large_list(size_t size)
{
	t_block	*ptr;
	t_block	*tmp;

	size = size + SIZE_ST_HEAD;
	size = ROUND_UP_PAGE(size, g_mem.page);
	size = (size) * g_mem.page;
	if ((tmp = (t_block *)mmap(NULL, size, FLAG_MALLOC, -1, 0)) == MAP_FAILED)
		return (NULL);
	tmp->size = size;
	tmp->info |= OPT_FREE;
	tmp->info |= OPT_MAP_HEAD;
	tmp->info |= OPT_LARGE;
	tmp->next = NULL;
	tmp->ptr = tmp->data;
	if (!(g_mem.m_large))
		return ((g_mem.m_large = tmp));
	ptr = g_mem.m_large;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = tmp;
	return (tmp);
}

void				*alloc_large(size_t size)
{
	t_block	*ptr;

	ptr = NULL;
	ptr = add_large_list(size);
	pthread_mutex_unlock(&(g_mem.mutex));
	return (((ptr && ptr != ((void *)-1)) ? ptr->data : NULL));
}
