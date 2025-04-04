/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

int	stack_size(t_stack *stack)
{
	int	size;

	size = 0;
	while (stack)
	{
		stack = stack->next;
		size++;
	}
	return (size);
}

int	find_max_position(t_stack **b)
{
	int		max_pos;
	int		max_index;
	int		i;
	t_stack	*current;

	current = *b;
	max_index = INT_MIN;
	max_pos = 0;
	i = 0;
	while (current)
	{
		if (current->index > max_index)
		{
			max_index = current->index;
			max_pos = i;
		}
		current = current->next;
		i++;
	}
	return (max_pos);
}

void	find_and_push_max(t_stack **a, t_stack **b)
{
	int	max_pos;
	int	size;
	int	moves;

	max_pos = find_max_position(b);
	size = stack_size(*b);
	if (max_pos <= size / 2)
	{
		moves = max_pos;
		while (moves-- > 0)
			rotate_b(b);
	}
	else
	{
		moves = size - max_pos;
		while (moves-- > 0)
			reverse_rotate_b(b);
	}
	push_a(b, a);
}
