/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_pointer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:43:19 by alfsanch          #+#    #+#             */
/*   Updated: 2024/12/04 18:43:22 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_base(unsigned long num, char *base, int *count)
{
	if (num >= 16)
		ft_putnbr_base(num / 16, base, count);
	*count += write(1, &base[num % 16], 1);
}

int	ft_convert_pointer(void *ptr)
{
	int	count;

	count = 0;
	count += write(1, "0x", 2);
	if (!ptr)
		count += write(1, "0", 1);
	else
		ft_putnbr_base((unsigned long)ptr, "0123456789abcdef", &count);
	return (count);
}
