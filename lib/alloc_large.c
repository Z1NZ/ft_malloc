/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_large.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 08:44:38 by srabah            #+#    #+#             */
/*   Updated: 2017/02/18 15:57:07 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block	*init_large(size_t size)
{
	t_block *ptr;

	ptr = (t_block *)mmap(NULL, (size + SIZE_ST_HEAD), FLAG_MALLOC, -1, 0);
	if (ptr == ((void *)-1))
		return (NULL);
	ptr->size = size;
	ptr->info |= OPT_FREE;
	ptr->info |= OPT_MAP_HEAD;
	ptr->ptr = ptr->data;
	ptr->next = NULL; 
	g_mem.size_large += size;
	g_mem.use_large += size;
	g_mem.m_large = ptr;
	return(ptr);
}

t_block	*find_large_space(size_t size)
{
	t_block	*ptr;
	t_block *tmp;

	tmp = NULL;
	ptr = g_mem.m_large;
	while(ptr)
	{
		if (!CHECK_BIT(ptr->info, OPT_FREE) && ptr->size >= size)
		{
			if (!tmp || (tmp->size - size) > (ptr->size - size))
				tmp = ptr;
		}
		ptr = ptr->next;
	}
	if (tmp)
		tmp->info |= OPT_FREE;
	return (tmp);
}

t_block	*add_large_list(size)
{
	t_block	*ptr;
	t_block	*tmp;

	ptr = g_mem.m_large;
	while(ptr->next)
		ptr = ptr->next;
	tmp = (t_block *)mmap(NULL, (size + SIZE_ST_HEAD), FLAG_MALLOC, -1, 0);
	if (tmp == ((void *)-1))
		return (NULL);
	tmp->size = size;
	tmp->info |= OPT_FREE;
	tmp->info |= OPT_MAP_HEAD;
	tmp->ptr = ptr->data;
	g_mem.size_large += size;
	g_mem.use_large += size;
	tmp->next = NULL;
	ptr->next = tmp;
	return(tmp);
}


void	*alloc_large(size_t size)
{
	t_block *ptr;

	ptr = NULL;
	if (g_mem.size_large == 0)
		ptr = init_large(size);
	else if ((g_mem.size_large - g_mem.use_large) >= size)
		ptr = find_large_space(size);
	if (!ptr)
		ptr = add_large_list(size);
	pthread_mutex_unlock(&(g_mem.mutex));
	return (((ptr && ptr != ((void *)-1)) ? ptr->data : NULL));
}
