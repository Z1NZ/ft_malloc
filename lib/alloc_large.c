/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_large.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 08:44:38 by srabah            #+#    #+#             */
/*   Updated: 2017/02/15 16:05:14 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "malloc.h"

void	*alloc_large(size_t size)
{
	void *ptr;

	ptr = NULL;

	size = 0;
	printf("%s\n", "merci de coder la fonction");
	pthread_mutex_unlock(&(mem.mutex));
	return(ptr);
}