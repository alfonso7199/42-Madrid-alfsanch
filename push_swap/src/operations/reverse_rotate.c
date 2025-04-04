/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void	rrotate(t_stack **head)
{
	t_stack	*tail;

	if (*head == NULL || (*head)->next == NULL)
		return ;
	tail = *head;
	while (tail->next != NULL)
		tail = tail->next;
	tail->next = *head;
	*head = tail;
	while (tail->next != *head)
		tail = tail->next;
	tail->next = NULL;
}

void	reverse_rotate_a(t_stack **stack_a)
{
	rrotate(stack_a);
	write(1, "rra\n", 4);
}

void	reverse_rotate_b(t_stack **stack_b)
{
	rrotate(stack_b);
	write(1, "rrb\n", 4);
}

void	reverse_rotate_ab(t_stack **stack_a, t_stack **stack_b)
{
	rrotate(stack_a);
	rrotate(stack_b);
	write(1, "rrr\n", 4);
}
