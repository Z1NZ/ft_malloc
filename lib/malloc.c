/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:23:41 by srabah            #+#    #+#             */
/*   Updated: 2017/03/10 13:33:57 by srabah           ###   ########.fr       */
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
	while(i < len)
	{
		((t_block *)(ptr))->data[i] = 0;
		i++;
	}
}

void	*calloc(size_t count, size_t size)
{
	void *ptr;

	if (size == 0)
		size = 1;
	ptr = malloc((count * size));
	if (ptr)
		set_zero_block(ptr);
	return(ptr);
}



void	*realloc(void *ptr, size_t size)
{
	char	*tmp;
	size_t	len;
	size_t	i;

	if (!ptr)
		return(malloc(size));
	else if (ptr && size == 0)
	{
		free(ptr);
		return(NULL);
	}
	else
	{
		ptr -= OFFSETOFF(t_block, data);
		len = ((t_block *)(ptr))->size - SIZE_ST_HEAD;
		if (len >= size)
			return(((t_block *)(ptr))->data);
		else
		{
			tmp = (void *)malloc(size);
			i = 0;
			while(i <= len)
			{
				tmp[i] = ((t_block *)(ptr))->data[i];
				i++;
			}
			free(((t_block *)(ptr))->data);
			return((void *)tmp);
		}
	}
	return(NULL);
}

void	*malloc(size_t size)
{
	size_t	len;
	size_t	len_small;

	pthread_mutex_lock(&(g_mem.mutex));
	if (g_mem.page == 0)
		g_mem.page = getpagesize();
	if (!g_mem.size_tyni && !g_mem.size_small)
		init_memory(100, 100);
	len = (size <= TYNI_MAX) ? 1 : (ROUND_UP_PAGE(size, TYNI_MAX));
	len_small = (size <= SMALL_MIN) ? 1 : (ROUND_UP_PAGE(size, SMALL_MIN));
	if (len <= 4)
		return (alloc_tyni(len));
	else if (len_small <= 4)
		return (alloc_small(len_small));
	else
		return (alloc_large(size));
}
