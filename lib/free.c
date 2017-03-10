/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 11:44:30 by srabah            #+#    #+#             */
/*   Updated: 2017/03/10 13:36:34 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static inline void	free_splite_block(t_block *ptr, size_t block_size)
{
	t_block *tmp;
	t_block *new;
	t_block *var;
	int		nb_block;
	int		i;

	tmp = ptr;
	i = 1;
	nb_block = tmp->size / block_size;
	var = ptr->next;
	ptr->info ^= OPT_FREE;
	ptr->size = block_size;
	ptr->ptr = ptr->data;
	while(i < nb_block)
	{
		new = (t_block*)(tmp->ptr + (block_size - SIZE_ST_HEAD));
		new->info = ptr->info;
		new->size = block_size;
		new->ptr = new->data;
		tmp->next = new;
		tmp = tmp->next;
		i++;
	}
	tmp->next = var;
}

static inline void	unmap_block(t_block **head, t_block *ptr)
{
	t_block *tmp;

	if (*head == ptr)
	{
		*head = ptr->next;
		if (munmap(ptr, ptr->size) == -1)
			write(2, "ERROR UNMAP_BLOCK_1\n", 20);
		return ;
	}
	tmp = *head;
	while(tmp)
	{
		if (tmp->next == ptr)
		{
			tmp->next = ptr->next;
			if (munmap(ptr, ptr->size) == -1)
				write(2, "ERROR UNMAP_BLOCK_2\n", 20);
			break;
		}
		tmp = tmp->next;
	}
}

static inline int	check_addr(void *ptr)
{
	t_block *tmp;
	int i;
	int j;

	i = 0;
	tmp = g_mem.m_tyni;
	loop:
	j = 0;
	while(tmp)
	{
		if (tmp->ptr == ptr)
			return (1);
		tmp = tmp->next;
		j++;
	}
	++i;
	if (i == 1)
		tmp = g_mem.m_small;
	else if (i == 2)
		tmp = g_mem.m_large;
	else
		return (0);
	goto loop;
}

void	free(void *ptr)
{
	pthread_mutex_lock(&(g_mem.mutex));
	if (!ptr)
	{
		pthread_mutex_unlock(&(g_mem.mutex));
		return ;
	}
	if ((check_addr(ptr)) > 0)
	{
		ptr -= OFFSETOFF(t_block, data);
		if (CHECK_BIT(((t_block *)(ptr))->info, OPT_TYNI))
		{
			g_mem.use_tyni -= ((t_block *)(ptr))->size;
			if (((t_block *)(ptr))->size > TYNI_BLOCK)
				free_splite_block(((t_block *)(ptr)), TYNI_BLOCK);
			else
				((t_block *)(ptr))->info ^= OPT_FREE;
		}
		else if (CHECK_BIT(((t_block *)(ptr))->info, OPT_SMALL))
		{
			g_mem.use_small -= ((t_block *)(ptr))->size;
			if (((t_block *)(ptr))->size > SMALL_BLOCK)
				free_splite_block(((t_block *)(ptr)), SMALL_BLOCK);
			else
				((t_block *)(ptr))->info ^= OPT_FREE;	
		}
		else if (CHECK_BIT(((t_block *)(ptr))->info, OPT_LARGE))
		{
			g_mem.use_large -= ((t_block *)(ptr))->size;
			g_mem.size_large -= ((t_block *)(ptr))->size;
			unmap_block(&g_mem.m_large, ptr);
		}
	 }
	pthread_mutex_unlock(&(g_mem.mutex));
}