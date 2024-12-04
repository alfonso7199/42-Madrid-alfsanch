/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_decimal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:42:45 by alfsanch          #+#    #+#             */
/*   Updated: 2024/12/04 18:42:48 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr(long n, int *count)
{
	char	c;

	if (n < 0)
	{
		*count += write(1, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr(n / 10, count);
	c = '0' + (n % 10);
	*count += write(1, &c, 1);
}

int	ft_convert_decimal(int num)
{
	int	count;

	count = 0;
	ft_putnbr(num, &count);
	return (count);
}
