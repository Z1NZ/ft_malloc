/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fusion_block.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:26:24 by srabah            #+#    #+#             */
/*   Updated: 2017/03/10 13:49:30 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** pointer sur la tete de list
** size nombre de block rechercher
**  return le pointer sur le premiere block a fusionne les autre se suive
**  sinon return NULL si il a pas trouver
*/

void	*find_fusion_location(t_block *block, size_t size)
{
	size_t	i;
	t_block *tmp;
	t_block *ptr;

	ptr = block;
	tmp = NULL;
	if (size == 1)
	{
		while(ptr)
		{
			if (!CHECK_BIT(ptr->info, OPT_FREE))
				return(ptr);
			ptr = ptr->next;
		}
	}
	ptr = block;
	while (ptr)
	{
		i = 0;
		tmp = ptr;
		while (tmp && (!CHECK_BIT(tmp->info, OPT_FREE)) && (!CHECK_BIT(tmp->info, OPT_MAP_HEAD)))
		{
			i++;
			if (i == size)
			{
				ptr->next = tmp->next;
				return (ptr);
			}
			tmp = tmp->next;
		}
		ptr = ptr->next;
	}
	return (NULL);
}
