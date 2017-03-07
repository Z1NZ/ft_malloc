/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2017/03/07 04:35:57 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*new_space;

	if (!size)
		return (NULL);
	new_space = (void*)mmap(NULL, (size * sizeof(void*)), FLAG_MALLOC, -1, 0);
	if (!new_space)
		return (NULL);
	ft_bzero(new_space, size);
	return (new_space);
}
