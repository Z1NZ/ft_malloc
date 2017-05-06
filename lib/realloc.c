/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 23:49:32 by srabah            #+#    #+#             */
/*   Updated: 2017/05/06 23:49:33 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void			*realloc_bloc(void *ptr, size_t size, size_t i)
{
	char	*tmp;
	size_t	len;

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

void				*realloc(void *ptr, size_t size)
{
	size_t	i;

	i = 0;
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
		return (realloc_bloc(ptr, size, i));
	return (unlock_return_null(&(g_mem.mutex_real)));
}
