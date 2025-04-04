/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "../libft/libft.h"

# define STDERR_FILENO 2

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

void		push(t_stack **src, t_stack **dest);
void		rotate(t_stack **head);
void		rrotate(t_stack **head);
void		swap(t_stack **head);

void		push_a(t_stack **a, t_stack **b);
void		push_b(t_stack **a, t_stack **b);
void		rotate_a(t_stack **a);
void		rotate_b(t_stack **b);
void		rotate_rr(t_stack **a, t_stack **b);
void		reverse_rotate_a(t_stack **a);
void		reverse_rotate_b(t_stack **b);
void		reverse_rotate_ab(t_stack **a, t_stack **b);
void		swap_a(t_stack **a);
void		swap_b(t_stack **b);
void		swap_ab(t_stack **a, t_stack **b);

int			stack_size(t_stack *stack);
int			is_sorted(t_stack *stack);
int			find_max_index(t_stack *stack);
void		append_node(t_stack **stack, int value);

void		sort_stack(t_stack **a, t_stack **b);
void		sort_three(t_stack **stack_a);
void		sort_five(t_stack **a, t_stack **b);
void		sort_large(t_stack **a, t_stack **b, int size);
void		find_and_push_max(t_stack **a, t_stack **b);
int			find_max_position(t_stack **b);

t_stack		*create_stack(int argc, char **argv);
void		assign_indexes(t_stack *stack, int stack_size);

int			has_duplicates(char **args);
int			is_valid_number(char *str);
void		validate_input(int argc, char **argv);

void		error_exit(char *message);
void		free_stack(t_stack **stack);
void		free_string_array(char **array);
void		process_chunk(t_stack **a, t_stack **b, int chunk_size,
				int *pushed_count);

#endif