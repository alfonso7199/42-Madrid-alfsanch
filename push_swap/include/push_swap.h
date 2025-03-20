#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include "../libft/libft.h"

typedef struct s_stack {
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;


void	swap(t_stack **head);
void	swap_a(t_stack **head);
void	swap_b(t_stack **head);
void	swap_ab(t_stack **stack_a, t_stack **stack_b);
void	push(t_stack **stack_from, t_stack **stack_to);
void	push_a(t_stack **stack_a, t_stack **stack_b);
void	push_b(t_stack **stack_a, t_stack **stack_b);
void	rotate(t_stack **head);
void	rotate_a(t_stack **head);
void	rotate_b(t_stack **head);
void	rotate_rr(t_stack **stack_a, t_stack **stack_b);
void	rrotate(t_stack **head);
void	reverse_rotate_a(t_stack **head);
void	reverse_rotate_b(t_stack **head);
void	reverse_rotate_ab(t_stack **stack_a, t_stack **stack_b);


#endif