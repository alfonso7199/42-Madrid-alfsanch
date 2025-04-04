/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_large(t_stack **a, t_stack **b, int size)
{
	int	chunks;
	int	chunk_size;
	int	current_chunk;
	int	pushed_count;

	chunks = 5;
	if (size > 100)
		chunks = 12;
	chunk_size = size / chunks;
	current_chunk = 1;
	pushed_count = 0;
	while (*a)
	{
		if ((*a)->index <= (current_chunk * chunk_size))
		{
			process_chunk(a, b, chunk_size, &pushed_count);
			if (pushed_count >= current_chunk * chunk_size)
				current_chunk++;
		}
		else
			rotate_a(a);
	}
	while (*b)
		find_and_push_max(a, b);
}
