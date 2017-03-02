/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 11:44:30 by srabah            #+#    #+#             */
/*   Updated: 2017/03/02 03:03:27 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "malloc.h"

static inline void	free_splite_block(t_block *ptr, size_t block_size, int type)
{
	t_block *tmp;
	t_block *new;
	int		nb_block;
	int		i;

	tmp = ptr;
	i = 1;
	nb_block = tmp->size / block_size;
	while(i < nb_block)
	{
		new = (t_block*) tmp->data + block_size - SIZE_ST_HEAD;
		tmp->next = new;
		tmp->size = block_size;
		ptr->info |= type;
		ptr->info ^= OPT_FREE;
		ptr->ptr = ptr->data;
		tmp = tmp->next;
		i++;
	}
}
// static inline void	check_unmap(t_block *ptr)
// {
// 	t_block *tmp;
// 	int		len;

// 	len = 0;
// 	tmp = ptr;
// 	while(tmp && len != g_mem.page)
// 	{
// 		if (!CHECK_BIT(ptr->info, OPT_FREE))
// 			len += ptr->size;
// 		else
// 			return ;
// 		tmp = tmp->next;
// 	}
// 	printf(GRN"%s\n"RESET , "SUPER PAGE   faire la fonction de getion des unmap");		
// }

static inline void	unmap_block(t_block **head, t_block *ptr)
{
	t_block *tmp;

	if (*head == ptr)
	{
		*head = ptr->next;
		munmap((caddr_t *)ptr, ptr->size);
		return ;
	}
	tmp = *head;
	while(tmp)
	{
		if (tmp->next == ptr)
		{
			tmp->next = ptr->next;
			munmap((caddr_t *)ptr, ptr->size);
			break;
		}
		tmp = tmp->next;
	}
}
static inline int	check_addr(void *ptr)
{
	t_block *tmp;
	int i;

	i = 0;

	tmp = g_mem.m_tyni;
	loop:
	while(tmp)
	{
		if (tmp->data == ptr)
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
	if (!ptr || !check_addr(ptr))
	{
		pthread_mutex_unlock(&(g_mem.mutex));
		return ;
	}

	ptr -= OFFSETOFF(t_block, data);
	((t_block *)(ptr))->info ^= OPT_FREE;
	if (CHECK_BIT(((t_block *)(ptr))->info, OPT_TYNI))
	{
		g_mem.use_tyni -= ((t_block *)(ptr))->size;
		if (((t_block *)(ptr))->size > TYNI_BLOCK)
			free_splite_block(((t_block *)(ptr)), TYNI_BLOCK, OPT_TYNI);
	
	}
	else if (CHECK_BIT(((t_block *)(ptr))->info, OPT_SMALL))
	{
		g_mem.use_small -= ((t_block *)(ptr))->size;
		if (((t_block *)(ptr))->size > SMALL_BLOCK)
			free_splite_block(((t_block *)(ptr)), SMALL_BLOCK, OPT_SMALL);
	}
	else if (CHECK_BIT(((t_block *)(ptr))->info, OPT_LARGE))
	{
		g_mem.use_large -= ((t_block *)(ptr))->size;
		g_mem.size_large -= ((t_block *)(ptr))->size;
		unmap_block(&g_mem.m_large, ptr);
		pthread_mutex_unlock(&(g_mem.mutex));
		return	;
	}
	// if (!CHECK_BIT(((t_block *)(ptr))->info, OPT_LARGE) && CHECK_BIT(((t_block *)(ptr))->info, OPT_MAP_HEAD))
	// {
	// 	write(2, "toto rina\n", 10);
	// }
	pthread_mutex_unlock(&(g_mem.mutex));
}