/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
Atoi converts a char string to an integer number
*/

int	ft_atoi(const char *str)
{
	int	neg;
	int	number;
	int	signs;

	neg = 1;
	number = 0;
	signs = 0;
	while ((*str == ' ' ) || (*str >= 9 && *str <= 13))
		++str;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg *= -1;
		++str;
		signs++;
		if (signs > 1)
			return (0);
	}
	while ((*str != 0) && (*str >= '0') && (*str <= '9'))
	{
		number = (number * 10) + (*str - '0');
		++str;
	}
	return (number * neg);
}

/*int main(void)
{
    const char *str1 = "   -123";
    printf("Conversion de '%s': %d\n", str1, ft_atoi(str1));
    return 0;
}*/