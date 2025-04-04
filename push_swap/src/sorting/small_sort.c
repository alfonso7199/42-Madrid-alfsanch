/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void	sort_three(t_stack **stack_a)
{
	int	max;

	max = find_max_index(*stack_a);
	if ((*stack_a)->index == max)
		rotate_a(stack_a);
	else if ((*stack_a)->next->index == max)
		reverse_rotate_a(stack_a);
	if ((*stack_a)->index > (*stack_a)->next->index)
		swap_a(stack_a);
}

void	sort_five(t_stack **a, t_stack **b)
{
	int	size;

	size = stack_size(*a);
	while (size-- > 0)
	{
		if ((*a)->index == 0 || (*a)->index == 1)
			push_b(a, b);
		else
			rotate_a(a);
	}
	sort_three(a);
	if (stack_size(*b) == 2)
	{
		if ((*b)->index < (*b)->next->index)
			swap_b(b);
	}
	push_a(b, a);
	push_a(b, a);
}
