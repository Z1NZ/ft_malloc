/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:23:41 by srabah            #+#    #+#             */
/*   Updated: 2017/03/14 19:47:57 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void				*malloc(size_t size)
{
	size_t	len;
	size_t	len_small;

	if (pthread_mutex_lock(&(g_mem.mutex)) == EINVAL)
	{
		pthread_mutex_init(&(g_mem.mutex), NULL);
		pthread_mutex_lock(&(g_mem.mutex));
	}
	if (g_mem.page == 0)
		g_mem.page = getpagesize();
	if (!g_mem.size_tyni && !g_mem.size_small)
		if (init_memory(100, 100) == 0)
		{
			pthread_mutex_unlock(&(g_mem.mutex));
			return (NULL);
		}
	len = (size <= TYNI_MAX) ? 1 : (ROUND_UP_PAGE(size, TYNI_MAX));
	len_small = (size <= SMALL_MIN) ? 1 : (ROUND_UP_PAGE(size, SMALL_MIN));
	if (len <= 4)
		return (alloc_tyni(len));
	else if (len_small <= 4)
		return (alloc_small(len_small));
	else
		return (alloc_large(size));
}
