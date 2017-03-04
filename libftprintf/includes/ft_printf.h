/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 20:43:17 by srabah            #+#    #+#             */
/*   Updated: 2015/03/04 20:43:44 by srabah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>

typedef struct	s_context
{
	int			ret;
	int			bitcode;
	int			width;
	int			precision;
	char		conversion;
}				t_context;

typedef int		t_pfn(va_list *ap);

/*
**	:::: Defines ::::
*/
# define STDOUT	1
# define CONTEXT(R)				pfunc_core_context_init()->R
# define BITCODE				CONTEXT(bitcode)
# define PRECISION				CONTEXT(precision)
# define WIDTH					CONTEXT(width)
# define CONVERSION				CONTEXT(conversion)
# define CONTEXT_RESET_FLUSH	(pfunc_core_context_reset(0))
# define CONTEXT_RESET_DEFAULT	(pfunc_core_context_reset(1))
# define UNKNOWN				'~'
# define UNICODE_SIZE			4

# define FLAG_SPACE				1
# define FLAG_ZERO				2
# define FLAG_SHARP				4
# define FLAG_DASH				8
# define FLAG_MORE				16
# define FLAG_LESS				32

# define MODIF_H				64
# define MODIF_HH				128
# define MODIF_L				256
# define MODIF_LL				512
# define MODIF_J				1024
# define MODIF_Z				2048

# define PREC_STATE				4096

# define C_IS_S_LOWER			(CONVERSION == 's')
# define C_IS_S_UPPER			(CONVERSION == 'S')
# define C_IS_C_LOWER			(CONVERSION == 'c')
# define C_IS_C_UPPER			(CONVERSION == 'C')
# define C_IS_D_LOWER			(CONVERSION == 'd')
# define C_IS_D_UPPER			(CONVERSION == 'D')
# define C_IS_P_LOWER			(CONVERSION == 'p')
# define C_IS_I_LOWER			(CONVERSION == 'i')
# define C_IS_U_LOWER			(CONVERSION == 'u')
# define C_IS_U_UPPER			(CONVERSION == 'U')
# define C_IS_O_LOWER			(CONVERSION == 'o')
# define C_IS_O_UPPER			(CONVERSION == 'O')
# define C_IS_X_LOWER			(CONVERSION == 'x')
# define C_IS_X_UPPER			(CONVERSION == 'X')
# define C_IS_PERCENT			(CONVERSION == '%')
# define C_IS_UNKNOWN			(!ft_strchr("sSpdDioOuUxXcC%", CONVERSION))

# define ABS(number)			(number < 0) ? -(number) : (number)

int				ft_printf(char *fmt, ...);

/*
**	:::: Writers ::::
*/
int				pfunc_writer_putchar(char c);
int				pfunc_writer_putstrn(char *str, size_t n);
int				pfunc_writer_putstr(char *str);
int				pfunc_writer_putnbr(long long n);
int				pfunc_writer_wputchar(wchar_t c);
int				pfunc_writer_wputstr(wchar_t *string);
void			pfunc_writer_wputstrn(wchar_t *wstring, int	n);

/*
**	:::: Core ::::
*/
int				pfunc_core_def(char *fmt, va_list *ap);
t_context		*pfunc_core_context_init(void);
int				pfunc_core_context_reset(int flush);
int				pfunc_core_conv(va_list *ap);

/*
**	:::: Parsers ::::
*/
int				pfunc_parser_def(char **fmt);
int				pfunc_parser_flag(char **fmt);
int				pfunc_parser_precision(char **fmt);
int				pfunc_parser_type(char **fmt);
int				pfunc_parser_width(char **fmt);
int				pfunc_parser_modifier(char **fmt);

/*
**	:::: Types ::::
*/
int				pfunc_type_s_lower(va_list *ap);
int				pfunc_type_s_upper(va_list *ap);
int				pfunc_type_c_lower(va_list *ap);
int				pfunc_type_c_upper(va_list *ap);
int				pfunc_type_d_lower(va_list *ap);
int				pfunc_type_d_upper(va_list *ap);
int				pfunc_type_p_lower(va_list *ap);
int				pfunc_type_i_lower(va_list *ap);
int				pfunc_type_u_lower(va_list *ap);
int				pfunc_type_u_upper(va_list *ap);
int				pfunc_type_o_lower(va_list *ap);
int				pfunc_type_o_upper(va_list *ap);
int				pfunc_type_x_lower(va_list *ap);
int				pfunc_type_x_upper(va_list *ap);
int				pfunc_type_default(va_list *ap);
int				pfunc_type_percent(va_list *ap);

/*
**	:::: Tools ::::
*/
char			*pfunc_tool_padding(char padder, size_t len);
int				pfunc_tool_intlen(unsigned long long number);
char			*pfunc_tool_itoa(unsigned long long n);
char			*pfunc_tool_signer(char *conv, long long number);
char			*pfunc_tool_usigner(char *conv, unsigned long long number);
char			*pfunc_tool_dectohex(unsigned long long number);
char			*pfunc_tool_dectooctal(unsigned long long number);
void			pfunc_tool_capitalize(char *str);
int				pfunc_tool_countbytes(int total_bits);
long long		pfunc_tool_bintodec(long long n);
char			*pfunc_tool_dectobin(unsigned long long number);
char			*pfunc_tool_unicode(char *binary);
int				pfunc_tool_wcharlen(wchar_t c);
int				pfunc_tool_wstrlen(wchar_t *wstring, int n);

#endif
