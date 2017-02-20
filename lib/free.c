/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 11:44:30 by srabah            #+#    #+#             */
/*   Updated: 2017/02/19 15:53:42 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "malloc.h"

void	free_splite_block(t_block *ptr, size_t block_size, int type)
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
		//gestion specifique du type large
	}
	if (CHECK_BIT(((t_block *)(ptr))->info, OPT_MAP_HEAD))
		printf(GRN"%s\n"RESET , "SUPER PAGE   faire la fonction de getion des unmap");		
}