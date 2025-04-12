/*
Write a program that takes a single string in snake_case format
and converts it into a string in lowerCamelCase format.

A snake_case string is a string where each word is in lower case, separated by
an underscore "_".

A lowerCamelCase string is a string where each word begins with a capital letter
except for the first one.
*/
#include <unistd.h>

void    putchar(char c)
{
    write(1, &c, 1);
}

int     isLower(int c)
{
    return (c >= 'a' && c <= 'z');
}

int     toUpper(int c)
{
    if (isLower(c))
        return (c - 32);
    return (c);
}

int     main(int ac, char **av)
{
    if (ac < 2)
    {
        putchar('\n');
        return (0);
    }
    int     i;

    i = 0;
    while (av[1][i])
    {
        if (av[1][i] == '_' && av[1][i + 1])
        {
            i++;
            putchar(toUpper(av[1][i]));
        }
        else 
            putchar(av[1][i]);
        i++;
    }
    putchar('\n');
    return (0);
}