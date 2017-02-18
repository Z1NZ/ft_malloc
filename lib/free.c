/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 11:44:30 by srabah            #+#    #+#             */
/*   Updated: 2017/02/18 16:01:08 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "malloc.h"


#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

void ft_free(void *ptr)
{
	ptr -= OFFSETOFF(t_block, data);
	((t_block *)(ptr))->info ^= OPT_FREE;

	if (CHECK_BIT(((t_block *)(ptr))->info, OPT_MAP_HEAD))
	{
		printf("GRN%sRESET \n", "SUPER PAGE   faire la fonction de getion des unmap");		
	}
	t_block *tmp;

	tmp = g_mem.m_small;
	int j = 0;
	while(tmp)
	{
		printf(RED"pos = [%d]"GRN"addr = [%p]" CYN "size = [%zu]"RESET" info = [%d]\n", j, tmp, tmp->size, tmp->info);
		if (ptr == tmp)
			printf(RED "\n\n\nONIZUKA\n\n\n" RESET);
		tmp = tmp->next;
		j++;
	}
}