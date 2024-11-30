/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:11:37 by alfsanch          #+#    #+#             */
/*   Updated: 2024/10/14 17:14:21 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int ft_process_format(const char *format, va_list args)
{
    int printed_chars = 0;

    while (*format)
    {
        if (*format == '%')
        {
            format++;
            if (*format == 'c')
                printed_chars += ft_convert_char(va_arg(args, int));
            else if (*format == 's')
                printed_chars += ft_convert_string(va_arg(args, char *));
            else if (*format == 'p')
                printed_chars += ft_convert_pointer(va_arg(args, void *));
            else if (*format == 'd' || *format == 'i')
                printed_chars += ft_convert_decimal(va_arg(args, int));
            else if (*format == 'u')
                printed_chars += ft_convert_unsigned(va_arg(args, unsigned int));
            else if (*format == 'x' || *format == 'X')
                printed_chars += ft_convert_xX(va_arg(args, unsigned int), *format);
            else if (*format == '%')
                printed_chars += ft_convert_percent();
        }
        else
        {
            write(1, format, 1);
            printed_chars++;
        }
        format++;
    }
    return printed_chars;
}

int ft_printf(const char *format, ...)
{
    va_list args;
    int result;

    va_start(args, format);
    result = ft_process_format(format, args);
    va_end(args);
    return result;
}