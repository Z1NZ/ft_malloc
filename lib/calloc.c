/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 23:47:15 by srabah            #+#    #+#             */
/*   Updated: 2017/05/06 23:47:17 by srabah           ###   ########.fr       */
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

void				*calloc(size_t count, size_t size)
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
