/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 11:44:30 by srabah            #+#    #+#             */
/*   Updated: 2017/03/09 16:37:26 by srabah           ###   ########.fr       */
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
	// ft_printf("FSB[%p] -> [%p] var -> [%p] nb %lu\n",ptr,ptr->next,var, nb_block);
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
		// ft_printf("[%p] size[%lu]\n", tmp, tmp->size);
		i++;
	}
		tmp->next = var;
}

static inline void	unmap_block(t_block **head, t_block *ptr)
{
	t_block *tmp;

	if (*head == ptr)
	{
		write(1,"FREE HEAD\n", 10);
		*head = ptr->next;
		if (munmap(ptr, ptr->size) == -1)
			write(2, "ERROR UNMAP_BLOCK_1\n", 20);
		return ;
	}
	tmp = *head;
	while(tmp)
	{
		if (tmp->next == ptr) // a verfier copier la fonction de check
		{
			write(1, "FREE LARGE\n", 11);
			ft_printf("tmp->next[%p] ptr[%p] ptr->next[%p]",tmp->next,ptr, ptr->next);
			tmp->next = ptr->next;
			ft_printf("\n\n\n\n%lu\n\n\n\n", ptr->size);
			if (munmap(ptr, ptr->size) == -1)
				write(2, "ERROR UNMAP_BLOCK_2\n", 20);
			ft_printf("tmp[%p] tmp->next[%p]",tmp,tmp->next);
			break;
		}
		tmp = tmp->next;
	}
}

static inline int	check_addr(void *ptr)
{
	write(1, "CHECK_ADDR\n", 11);
	t_block *tmp;
	int i;
	int j;

	i = 0;
	tmp = g_mem.m_tyni;
	loop:
	j = 0;
	ft_printf("HEAD===[%p]====[%p]\n",g_mem.m_large, ptr);
	ft_mem_show(OPT_LARGE);
	while(tmp)
	{
		// ft_printf("%p == %p\n",  tmp->ptr, ptr);
	 	// ft_printf(RED"pos = [%d]"GRN"addr = [%p]" CYN "size = [%zu]"RESET" info = [%d]\n", j, tmp, tmp->size, tmp->info);
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
	write(1, "TOTO\n", 5);
	if (!ptr)
	{
		write(1, "F_NULL\n", 7);
		pthread_mutex_unlock(&(g_mem.mutex));
		return ;
	}
	write(1, "SISI\n", 5);
	if ((check_addr(ptr)) > 0)
	{
		write(1, "INSIDE\n", 7);
		ptr -= OFFSETOFF(t_block, data);
		if (CHECK_BIT(((t_block *)(ptr))->info, OPT_TYNI))
		{
			write(1, "ICI\n", 4);
			g_mem.use_tyni -= ((t_block *)(ptr))->size;
			if (((t_block *)(ptr))->size > TYNI_BLOCK)
				free_splite_block(((t_block *)(ptr)), TYNI_BLOCK);
			else
				((t_block *)(ptr))->info ^= OPT_FREE;
		}
		else if (CHECK_BIT(((t_block *)(ptr))->info, OPT_SMALL))
		{
			write(1, "LA!\n", 4);
			g_mem.use_small -= ((t_block *)(ptr))->size;
			if (((t_block *)(ptr))->size > SMALL_BLOCK)
				free_splite_block(((t_block *)(ptr)), SMALL_BLOCK);
			else
				((t_block *)(ptr))->info ^= OPT_FREE;	
		}
		else if (CHECK_BIT(((t_block *)(ptr))->info, OPT_LARGE))
		{
			write(1, "ENFIN\n", 6);
			g_mem.use_large -= ((t_block *)(ptr))->size;
			g_mem.size_large -= ((t_block *)(ptr))->size;
			unmap_block(&g_mem.m_large, ptr);
		}
	 }
	 write(1, "F_FIN\n", 6);
	pthread_mutex_unlock(&(g_mem.mutex));
}