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

static inline void	set_zero_block(void *ptr)
{
	size_t len;
	size_t i;

	i = 0;
	ptr -= OFFSETOFF(t_block, data);
	len = ((t_block *)(ptr))->size - SIZE_ST_HEAD;
	while (i < len)
	{
		((t_block *)(ptr))->data[i] = 0;
		i++;
	}
}

void	*calloc(size_t count, size_t size)
{
	void *ptr;

	if (pthread_mutex_lock(&(g_mem.mutex_cal)) == EINVAL)
	{
		pthread_mutex_init(&(g_mem.mutex_cal), NULL);
		pthread_mutex_lock(&(g_mem.mutex_cal));
	}
	if (size == 0)
		size = 1;
	ptr = malloc((count * size));
	if (ptr)
		set_zero_block(ptr);
	pthread_mutex_unlock(&(g_mem.mutex_cal));
	return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
	char	*tmp;
	size_t	len;
	size_t	i;

	if (pthread_mutex_lock(&(g_mem.mutex_real)) == EINVAL)
	{
		pthread_mutex_init(&(g_mem.mutex_real), NULL);
		pthread_mutex_lock(&(g_mem.mutex_real));
	}
	if (!ptr)
	{
		ptr = malloc(size);
		pthread_mutex_unlock(&(g_mem.mutex_real));
		return (ptr);
	}
	else if (ptr && size == 0)
	{
		free(ptr);
		pthread_mutex_unlock(&(g_mem.mutex_real));
		return (NULL);
	}
	else if ((check_addr(ptr)) == 0)
		return (unlock_return_null(&(g_mem.mutex_real)));
	else
	{
		ptr -= OFFSETOFF(t_block, data);
		len = ((t_block *)(ptr))->size - SIZE_ST_HEAD;
		if (len >= size)
		{
			pthread_mutex_unlock(&(g_mem.mutex_real));
			return (((t_block *)(ptr))->data);
		}
		else
		{
			if ((tmp = (void *)malloc(size)))
			{
				i = 0;
				while (i < len)
				{
					tmp[i] = ((t_block *)(ptr))->data[i];
					i++;
				}
				free(((t_block *)(ptr))->data);
			}
			pthread_mutex_unlock(&(g_mem.mutex_real));
			return (tmp);
		}
	}
	return (unlock_return_null(&(g_mem.mutex_real)));
}

void	*malloc(size_t size)
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
