/*
Assignment name  : ft_strdup
Expected files   : ft_strdup.c
Allowed functions: malloc
--------------------------------------------------------------------------------

Reproduce the behavior of the function strdup (man strdup).

Your function must be declared as follows:

char    *ft_strdup(char *src);
*/
#include <stdlib.h>
char    *ft_strdup(char *src)
{
    int len = 0;
    char *src2;
    int i = 0;

    while (src[len])
    {
        len++;
    }
    src2 = malloc((len + 1) * sizeof(char));
    if (!src2)
        return (NULL);
    while (src[i])
    {
        src2[i] = src[i];
        i++;
    }

    src2[i] = '\0';
    return (src2);
}