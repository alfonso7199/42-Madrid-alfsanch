/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void	assign_indexes(t_stack *stack, int stack_size)
{
	t_stack	*current;
	t_stack	*max_node;
	int		max_value;

	while (stack_size-- > 0)
	{
		max_value = INT_MIN;
		max_node = NULL;
		current = stack;
		while (current)
		{
			if (!current->index && current->value >= max_value)
			{
				max_value = current->value;
				max_node = current;
			}
			current = current->next;
		}
		if (max_node)
			max_node->index = stack_size;
	}
}
