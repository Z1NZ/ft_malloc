/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.parser.modifier.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:13:54 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void		pfunc_parser_modifier_l(void)
{
	if (!(BITCODE & MODIF_L) && !(BITCODE & MODIF_LL))
		BITCODE |= MODIF_L;
	else if ((BITCODE & MODIF_L) && !(BITCODE & MODIF_LL))
		BITCODE |= MODIF_LL;
	else if (BITCODE & MODIF_LL)
		BITCODE ^= MODIF_LL;
}

static void		pfunc_parser_modifier_h(void)
{
	if (!(BITCODE & MODIF_H) && !(BITCODE & MODIF_HH))
		BITCODE |= MODIF_H;
	else if ((BITCODE & MODIF_H) && !(BITCODE & MODIF_HH))
		BITCODE |= MODIF_HH;
	else if (BITCODE & MODIF_HH)
		BITCODE ^= MODIF_HH;
}

int				pfunc_parser_modifier(char **fmt)
{
	int		modifier;

	modifier = 0;
	while (ft_strchr("lhjz", **fmt))
	{
		if (**fmt == 'l')
			pfunc_parser_modifier_l();
		else if (**fmt == 'h')
			pfunc_parser_modifier_h();
		else if (**fmt == 'j')
			BITCODE |= MODIF_J;
		else if (**fmt == 'z')
			BITCODE |= MODIF_Z;
		modifier++;
		(*fmt)++;
	}
	if (BITCODE & MODIF_L || BITCODE & MODIF_LL)
	{
		(BITCODE & MODIF_H) ? BITCODE ^= MODIF_H : ' ';
		(BITCODE & MODIF_HH) ? BITCODE ^= MODIF_HH : ' ';
	}
	return (modifier);
}
