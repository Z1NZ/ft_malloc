/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_large.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 08:44:38 by srabah            #+#    #+#             */
/*   Updated: 2017/03/09 16:02:45 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block	*init_large(size_t size)
{
	t_block *ptr;

	size = size + SIZE_ST_HEAD;
	size = (size/g_mem.page) + 1;
	size = size * g_mem.page;
	ptr = (t_block *)mmap(NULL, size, FLAG_MALLOC, -1, 0);
	if (ptr == ((void *)-1))
		return (NULL);
	ptr->size = size;
	ptr->info |= OPT_FREE;
	ptr->info |= OPT_MAP_HEAD;
	ptr->info |= OPT_LARGE;
	ptr->ptr = ptr->data;
	ptr->next = NULL; 
	g_mem.size_large += size;
	g_mem.use_large += size;
	g_mem.m_large = ptr;
	return(ptr);
}

static t_block	*find_large_space(size_t size)
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

static t_block	*add_large_list(size_t size)
{
	t_block	*ptr;
	t_block	*tmp;

	ptr = g_mem.m_large;
	if (!ptr)
		return(NULL);
	while(ptr->next)
		ptr = ptr->next;
	size = size + SIZE_ST_HEAD;
	size = (size/g_mem.page) + 1;
	size = size * g_mem.page;
	ft_printf("%lu\n", size);
	tmp = (t_block *)mmap(NULL, size, FLAG_MALLOC, -1, 0);
	if (tmp == ((void *)-1))
		return (NULL);
	tmp->size = size;
	tmp->info |= OPT_FREE;
	tmp->info |= OPT_MAP_HEAD;
	tmp->info |= OPT_LARGE;
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

	write(2, "LARGE\n", 6);
	ptr = NULL;
	if (g_mem.size_large == 0)
		ptr = init_large(size);
	else if ((g_mem.size_large - g_mem.use_large) >= size)
	{
		write(1, "SISI\n", 5);
		ptr = find_large_space(size);
		if (ptr)
			g_mem.use_large += ptr->size;
	}
	if (!ptr)
	{
		write(1, "SUPEE\n", 6);
		ptr = add_large_list(size);
	}
	if (!ptr)
		write(2, "LARGE_NULL\n", 11);
	// ft_mem_show();
	write(2, "LARGE_FIN\n", 10);
	pthread_mutex_unlock(&(g_mem.mutex));
	return (((ptr && ptr != ((void *)-1)) ? ptr->data : NULL));
}
