/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 11:44:30 by srabah            #+#    #+#             */
/*   Updated: 2017/03/06 11:47:23 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "malloc.h"

static inline void	free_splite_block(t_block *ptr, size_t block_size, int type)
{
	t_block *tmp;
	t_block *tmp2;
	t_block *new;
	int		nb_block;
	int		i;


	tmp = ptr;
	i = 1;
	nb_block = tmp->size / block_size;
	tmp2 = ptr->next;
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
	// ft_printf("[%p]\n", tmp->next);
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
static inline int	check_addr(void *ptr) /// mega probleme sur le check 
{
	t_block *tmp;
	int i;

	i = 0;

	tmp = g_mem.m_tyni;
	loop:
		write(1, "free_007\n", 9);
	while(tmp)
	{
		if (tmp->ptr == ptr)
			return (1);
		tmp = tmp->next;
		// write(1, "free_007\n", 9);
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
	write(1, "free\n", 5);
	t_block *tmp;
	tmp -= OFFSETOFF(t_block, ptr);

	printf(RED "addr = [%p]\n"CYN "size = [%zu]\n"RESET" info = [%d]\n", tmp, tmp->size, tmp->info);

	pthread_mutex_lock(&(g_mem.mutex));
	if (!ptr || !check_addr(ptr))
	{
		write(1, "free_fi0\n", 9);
		pthread_mutex_unlock(&(g_mem.mutex));
		return ;
	}
	write(1, "ptr exxxxxi\n", 13);
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
		write(1, "free_fi2\n", 9);
		g_mem.use_small -= ((t_block *)(ptr))->size;
		if (((t_block *)(ptr))->size > SMALL_BLOCK)
			free_splite_block(((t_block *)(ptr)), SMALL_BLOCK, OPT_SMALL);
	}
	else if (CHECK_BIT(((t_block *)(ptr))->info, OPT_LARGE))
	{
		write(1, "free_fi3\n", 9);
		g_mem.use_large -= ((t_block *)(ptr))->size;
		g_mem.size_large -= ((t_block *)(ptr))->size;
		unmap_block(&g_mem.m_large, ptr);
	}
	write(1, "toto\n", 5);
	pthread_mutex_unlock(&(g_mem.mutex));
}