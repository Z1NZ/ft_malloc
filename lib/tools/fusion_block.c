/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fusion_block.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:26:24 by srabah            #+#    #+#             */
/*   Updated: 2017/02/27 08:35:34 by srabah           ###   ########.fr       */
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
	dprintf(2, "FUSION\n");
	while (ptr)
	{
		i = 0;
		tmp = ptr;
		while (tmp && (!CHECK_BIT(tmp->info, OPT_FREE))) /// verifer que il ny a pas de tete page entre les fusion 
		{
			i++;
			if (i == size)
			{
			dprintf(2, "FUSION PTR = %p	"   RED     "ptr->info = %d	 ptr->size = %lu\n"RESET, tmp, ptr->info, tmp->size);
				ptr->next = tmp->next;
				return (ptr);
			}
			tmp = tmp->next;
		}
		ptr = ptr->next;
	}
	return (NULL);
}
