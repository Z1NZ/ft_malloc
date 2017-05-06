/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fusion_block.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:26:24 by srabah            #+#    #+#             */
/*   Updated: 2017/03/14 20:30:48 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** 	pointer sur la tete de list
** 	size nombre de block rechercher
**  return le pointer sur le premiere block a fusionne les autre se suive
**  sinon return NULL si il a pas trouver
*/

static void	*simple_bloc(t_block *block)
{
	t_block *ptr;

	ptr = block;
	while (ptr)
	{
		if (!CHECK_BIT(ptr->info, OPT_FREE))
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

void		*find_fusion_location(t_block *block, size_t size)
{
	size_t	i;
	t_block *tmp;
	t_block *ptr;

	ptr = block;
	if (size == 1)
		return (simple_bloc(block));
	ptr = block;
	while (ptr)
	{
		i = 0;
		tmp = ptr;
		while (tmp && (!CHECK_BIT(tmp->info, OPT_FREE))
				&& (!CHECK_BIT(tmp->info, OPT_MAP_HEAD)))
		{
			if (++i == size)
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
