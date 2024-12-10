/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:44:52 by alfsanch          #+#    #+#             */
/*   Updated: 2024/12/04 18:44:54 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_format(const char *str, va_list args)
{
	if (*str == 'c')
		return (ft_convert_char(va_arg(args, int)));
	else if (*str == 's')
		return (ft_convert_string(va_arg(args, char *)));
	else if (*str == 'p')
		return (ft_convert_pointer(va_arg(args, void *)));
	else if (*str == 'd' || *str == 'i')
		return (ft_convert_decimal(va_arg(args, int)));
	else if (*str == 'u')
		return (ft_convert_unsigned(va_arg(args, unsigned int)));
	else if (*str == 'x' || *str == 'X')
		return (ft_convert_xX(va_arg(args, unsigned int), *str));
	else if (*str == '%')
		return (ft_convert_percentage());
	else
		return (ft_convert_char(*str));

}

static int	ft_str(const char *str, va_list args)
{
	int	p_chars;

	p_chars = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if (*str)
				p_chars += ft_format(str, args);
		}
		else
			p_chars += ft_print_char(*str);
		str++;
	}
	return (p_chars);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		result;

	va_start(args, format);
	result = ft_str(format, args);
	va_end(args);
	return (result);
}
