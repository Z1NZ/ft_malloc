/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 11:44:30 by srabah            #+#    #+#             */
/*   Updated: 2017/03/08 09:29:32 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static inline void	free_splite_block(t_block *ptr, size_t block_size, int type)
{
	t_block *tmp;
	t_block *new;
	t_block	*var;
	int		nb_block;
	int		i;

	tmp = ptr;
	if (ptr->next == NULL)
		var = NULL;
	else
		var = ptr->next->next;
	i = 0;
	nb_block = tmp->size / block_size;
	ptr->info ^= OPT_FREE;
	ptr->size = block_size;
	ptr->ptr = ptr->data;
	while(i < nb_block)
	{
		new = (t_block*)(tmp->ptr + (block_size - SIZE_ST_HEAD));
		tmp->size = block_size;
		new->info = ptr->info;
		new->info |= type;
		new->size = block_size;
		new->ptr = new->data;
		tmp->next = new;
		tmp = tmp->next;
		i++;
	}
	tmp->next = var;
}

// static inline void	unmap_block(t_block **head, t_block *ptr)
// {
// 	t_block *tmp;

// 	if (*head == ptr)
// 	{
// 		*head = ptr->next;
// 		munmap((caddr_t *)ptr, ptr->size);
// 		return ;
// 	}
// 	tmp = *head;
// 	while(tmp)
// 	{
// 		if (tmp->next == ptr) // a verfier copier la fonction de check
// 		{
// 			tmp->next = ptr->next;
// 			munmap((caddr_t *)ptr, ptr->size);
// 			break;
// 		}
// 		tmp = tmp->next;
// 	}
// }

static inline int	check_addr(void *ptr)
{
	t_block *tmp;
	int i;

	i = 0;
	tmp = g_mem.m_tyni;
	loop:
	while(tmp)
	{

		if (tmp->ptr == ptr)
			return (1);
		tmp = tmp->next;
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
				free_splite_block(((t_block *)(ptr)), TYNI_BLOCK, OPT_TYNI);
			else
				((t_block *)(ptr))->info ^= OPT_FREE;
		}
	// 	// else if (CHECK_BIT(((t_block *)(ptr))->info, OPT_SMALL))
	// 	// {
	// 	// 	g_mem.use_small -= ((t_block *)(ptr))->size;
	// 	// 	if (((t_block *)(ptr))->size > SMALL_BLOCK)
	// 	// 		free_splite_block(((t_block *)(ptr)), SMALL_BLOCK, OPT_SMALL);
	// 	// 	else
	// 	// 		((t_block *)(ptr))->info ^= OPT_FREE;	
	// 	// }
	// 	// else if (CHECK_BIT(((t_block *)(ptr))->info, OPT_LARGE))
	// 	// {
	// 	// 	g_mem.use_large -= ((t_block *)(ptr))->size;
	// 	// 	g_mem.size_large -= ((t_block *)(ptr))->size;
	// 	// 	unmap_block(&g_mem.m_large, ptr);
	// 	// }
	 }
	pthread_mutex_unlock(&(g_mem.mutex));
}