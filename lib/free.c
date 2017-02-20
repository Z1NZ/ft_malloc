/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 11:44:30 by srabah            #+#    #+#             */
/*   Updated: 2017/02/20 16:55:26 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "malloc.h"

static inline void	free_splite_block(t_block *ptr, size_t block_size, int type)
{
	t_block *tmp;
	t_block *new;
	int		nb_block;

	tmp = ptr;
	nb_block = tmp->size / block_size;
	while(nb_block)
	{
		new = tmp->ptr + (block_size - SIZE_ST_HEAD);
		tmp->next = new;
		tmp->size = block_size;
		ptr->info |= type;
		ptr->info ^= OPT_FREE;
		ptr->ptr = ptr->data;
		tmp = tmp->next;
		nb_block--;
	}

}
static inline void	check_unmap(t_block *ptr)
{
	t_block *tmp;
	size_t	len;

	len = 0;
	tmp = ptr;
	while(tmp && len != g_mem.page)
	{
		if (!CHECK_BIT(ptr->info, OPT_FREE))
			len += ptr->size;
		else
			return ;
		tmp = tmp->next;
	}
	printf(GRN"%s\n"RESET , "SUPER PAGE   faire la fonction de getion des unmap");		
}

void	ft_free(void *ptr)
{

	if (ptr == NULL)
		return ;
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
		// gestion du free et du unmap specifique avec buff 
		//gestion specifique du type large
	}
	if (!CHECK_BIT(((t_block *)(ptr))->info, OPT_LARGE) && CHECK_BIT(((t_block *)(ptr))->info, OPT_MAP_HEAD))
	{
		check_unmap(ptr);
	}
}