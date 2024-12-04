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

static int	ft_process_format(const char *format, va_list args)
{
	int	p_chars;

	p_chars = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'c')
				p_chars += ft_convert_char(va_arg(args, int));
			else if (*format == 's')
				p_chars += ft_convert_string(va_arg(args, char *));
			else if (*format == 'p')
				p_chars += ft_convert_pointer(va_arg(args, void *));
			else if (*format == 'd' || *format == 'i')
				p_chars += ft_convert_decimal(va_arg(args, int));
			else if (*format == 'u')
				p_chars += ft_convert_unsigned(va_arg(args, unsigned int));
			else if (*format == 'x' || *format == 'X')
				p_chars += ft_convert_xX(va_arg(args, unsigned int), *format);
			else if (*format == '%')
				p_chars += ft_convert_percentage();
		}
		else
		{
			write(1, format, 1);
			p_chars++;
		}
		format++;
	}
	return (p_chars);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		result;

	va_start(args, format);
	result = ft_process_format(format, args);
	va_end(args);
	return (result);
}
