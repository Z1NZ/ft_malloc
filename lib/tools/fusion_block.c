/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fusion_block.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 15:12:55 by srabah            #+#    #+#             */
/*   Updated: 2017/02/15 15:53:56 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "malloc.h"



/*
** pointer sur la tete de list 
** size nombre de block rechercher 
**      return le pointer sur le premiere block a fusionne les autre se suive
**  sinon return NULL si il a pas trouver 
*/

void	*find_fusion_location(t_block *block, size_t size)
{
	size_t	i;
	t_block *tmp;
	t_block *ptr;

	ptr = block;
	tmp = NULL;
	while(ptr)
	{
		i = 0;
		tmp = ptr;
		while(tmp && (!CHECK_BIT(tmp->info, OPT_FREE)))
		{
			i++;
			if (i == size)
			{
				ptr->next = tmp->next;
				return(ptr);
			}
			tmp = tmp->next;
		}
		ptr = ptr->next;
	}
	return(NULL);
}
