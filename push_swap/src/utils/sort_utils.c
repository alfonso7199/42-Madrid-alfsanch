/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

int	find_max_index(t_stack *stack)
{
	int		max;
	t_stack	*current;

	max = INT_MIN;
	current = stack;
	while (current)
	{
		if (current->index > max)
			max = current->index;
		current = current->next;
	}
	return (max);
}

int	is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

void	process_chunk(t_stack **a, t_stack **b, int chunk_size,
	int *pushed_count)
{
	push_b(a, b);
	(*pushed_count)++;
	if ((*b)->index < (chunk_size * (*pushed_count / chunk_size + 1))
		- (chunk_size / 2))
		rotate_b(b);
}

void	append_node(t_stack **stack, int value)
{
	t_stack	*new_node;
	t_stack	*last;

	new_node = malloc(sizeof(t_stack));
	if (!new_node)
		error_exit("Error con malloc");
	new_node->value = value;
	new_node->index = 0;
	new_node->next = NULL;
	if (*stack == NULL)
	{
		*stack = new_node;
		return ;
	}
	last = *stack;
	while (last->next)
		last = last->next;
	last->next = new_node;
}
