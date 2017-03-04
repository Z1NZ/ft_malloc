/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfunc.core.conv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <srabah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:11:58 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:13:09 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static t_pfn	*pfunc_core_conv_redirector_dioux(void)
{
	if (C_IS_D_LOWER)
		return (pfunc_type_d_lower);
	else if (C_IS_D_UPPER)
		return (pfunc_type_d_upper);
	else if (C_IS_P_LOWER)
		return (pfunc_type_p_lower);
	else if (C_IS_I_LOWER)
		return (pfunc_type_i_lower);
	else if (C_IS_U_LOWER)
		return (pfunc_type_u_lower);
	else if (C_IS_U_UPPER)
		return (pfunc_type_u_upper);
	else if (C_IS_O_LOWER)
		return (pfunc_type_o_lower);
	else if (C_IS_O_UPPER)
		return (pfunc_type_o_upper);
	else if (C_IS_X_LOWER)
		return (pfunc_type_x_lower);
	else if (C_IS_X_UPPER)
		return (pfunc_type_x_upper);
	else
		return (NULL);
}

static t_pfn	*pfunc_core_conv_redirector_basic(void)
{
	if (C_IS_S_LOWER)
		return (pfunc_type_s_lower);
	else if (C_IS_S_UPPER)
		return (pfunc_type_s_upper);
	else if (C_IS_C_LOWER)
		return (pfunc_type_c_lower);
	else if (C_IS_C_UPPER)
		return (pfunc_type_c_upper);
	else if (C_IS_PERCENT)
		return (pfunc_type_percent);
	else
		return (NULL);
}

static t_pfn	*pfunc_core_conv_redirector(void)
{
	t_pfn	*conv_function;

	conv_function = NULL;
	conv_function = pfunc_core_conv_redirector_dioux();
	if (conv_function)
		return (conv_function);
	conv_function = pfunc_core_conv_redirector_basic();
	if (conv_function)
		return (conv_function);
	return (pfunc_type_default);
}

int				pfunc_core_conv(va_list *ap)
{
	t_pfn	*conv_function;

	conv_function = NULL;
	conv_function = pfunc_core_conv_redirector();
	if (conv_function)
	{
		conv_function(ap);
		return (1);
	}
	else
		return (0);
}
