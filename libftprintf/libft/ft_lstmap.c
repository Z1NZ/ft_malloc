/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:41:33 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_item;
	t_list	*origin_list;
	t_list	*previous;

	if (!lst || !f)
		return (NULL);
	new_item = (*f)(lst);
	previous = new_item;
	origin_list = new_item;
	lst = lst->next;
	while (lst)
	{
		new_item = f(lst);
		if (new_item == NULL)
			return (NULL);
		previous->next = new_item;
		previous = new_item;
		lst = lst->next;
	}
	new_item->next = NULL;
	return (origin_list);
}
