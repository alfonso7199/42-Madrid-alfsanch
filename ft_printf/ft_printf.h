/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:45:36 by alfsanch          #+#    #+#             */
/*   Updated: 2024/12/04 18:45:42 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int	ft_printf(char const *format, ...);
int	ft_convert_char(char c);
int	ft_convert_string(const char *str);
int	ft_convert_pointer(void *ptr);
int	ft_convert_decimal(int num);
int	ft_convert_unsigned(unsigned int num);
int	ft_convert_hexa(unsigned int num, char format);
int	ft_convert_percentage(void);

#endif
