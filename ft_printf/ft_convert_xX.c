/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_xX.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:43:57 by alfsanch          #+#    #+#             */
/*   Updated: 2024/12/04 18:44:00 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_base(unsigned int num, char *base, int *count)
{
	if (num >= 16)
		ft_putnbr_base(num / 16, base, count);
	*count += write(1, &base[num % 16], 1);
}

int	ft_convert_xx(unsigned int num, char formateo)
{
	int		count;
	char	*base;

	count = 0;
	if (formateo == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	ft_putnbr_base(num, base, &count);
	return (count);
}