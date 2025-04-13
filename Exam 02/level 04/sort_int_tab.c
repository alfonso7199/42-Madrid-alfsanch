/*
Write the following function:

void sort_int_tab(int *tab, unsigned int size);

It must sort (in-place) the 'tab' int array, that contains exactly 'size'
members, in ascending order.

Doubles must be preserved.

Input is always coherent.
*/
void swap(int *a, int *b){
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}
void sort_int_tab(int *tab, unsigned int size)
{
    int i = 0;
    int j = 0;

    while (i < size)
    {
        j = 0;
        while (j < (size -1))
        {
            if (tab[j] > tab[j + 1])
                swap(&tab[j], &tab[j + 1]);
            j++;
        }
        i++;
    }
}