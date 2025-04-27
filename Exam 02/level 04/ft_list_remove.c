/*
Write a function called ft_list_remove_if that removes from the
passed list any element the data of which is "equal" to the reference data.

It will be declared as follows :

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)());

cmp takes two void* and returns 0 when both parameters are equal.

You have to use the ft_list.h file, which will contain:
*/
typedef struct      s_list
{
    struct s_list   *next;
    void            *data;
}                   t_list;

#include <stdlib.h>

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
    t_list *temp;

    if (*begin_list == NULL)
        return;

    if (cmp((*begin_list)->data, data_ref) == 0)
    {
        temp = *begin_list;
        *begin_list = (*begin_list)->next;
        free(temp);
        ft_list_remove_if(begin_list, data_ref, cmp);
    }
    else
    {
        ft_list_remove_if(&((*begin_list)->next), data_ref, cmp);
    }
}
