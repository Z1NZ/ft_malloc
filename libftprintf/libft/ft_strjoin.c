/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:22:05 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	if ((new_str = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
	{
		new_str = ft_strcpy(new_str, s1);
		new_str = ft_strcat(new_str, s2);
		return (new_str);
	}
	else
		return (NULL);
}
