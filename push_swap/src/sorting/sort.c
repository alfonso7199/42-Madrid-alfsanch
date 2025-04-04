/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void	sort_stack(t_stack **a, t_stack **b)
{
	int	size;

	size = stack_size(*a);
	if (is_sorted(*a))
		return ;
	if (size <= 3)
		sort_three(a);
	else if (size <= 5)
		sort_five(a, b);
	else
		sort_large(a, b, size);
}
