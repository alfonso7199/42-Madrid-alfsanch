/*
Write the following functions:

t_list	*sort_list(t_list* lst, int (*cmp)(int, int));

This function must sort the list given as a parameter, using the function
pointer cmp to select the order to apply, and returns a pointer to the
first element of the sorted list.

Duplications must remain.

Inputs will always be consistent.

You must use the type t_list described in the file list.h
that is provided to you. You must include that file
(#include "list.h"), but you must not turn it in. We will use our own
to compile your assignment.

Functions passed as cmp will always return a value different from
0 if a and b are in the right order, 0 otherwise.
*/

#include <stdlib.h>
#include "list.h"

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
typedef struct s_list
{
	int				data;
	struct s_list	*next;
}	t_list;

t_list *sort_list(t_list *lst, int (*cmp)(int, int))
{
    t_list *i;
    t_list *j;

    i = lst;
    while (i != NULL)
    {
        j = i->next;
        while (j != NULL)
        {
            if (cmp(i->data, j->data) == 0)
                ft_swap(&i->data, &j->data);
            j = j->next;
        }
        i = i->next;
    }
    return (lst);
}