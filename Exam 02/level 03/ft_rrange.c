#include <stdlib.h>

int *ft_rrange(int start, int end)
{
    int *range;
    int size;
    int i;

    if (start > end)
        size = start - end + 1;
    else
        size = end - start + 1;

    range = (int *)malloc(size * sizeof(int));
    i = 0;
    while (i < size)
    {
        range[i] = end;
        if (end > start)
            end--;
        else
            end++;
        i++;
    }

    return range;
} 