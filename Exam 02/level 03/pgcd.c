/*
Write a program that takes two strings representing two strictly positive
integers that fit in an int.

Display their highest common denominator followed by a newline (It's always a
strictly positive integer).

If the number of parameters is not 2, display a newline.
*/
#include <stdio.h>
#include <stdlib.h>

unsigned int gcd(unsigned int a, unsigned int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int main(int ac, char **av)
{
    if (ac == 3)
    {
        int a = atoi(av[1]);
        int b = atoi(av[2]);

        if (a > 0 && b > 0)
        {
            printf("%d", gcd(a, b));
        }
    }
    printf("\n");
    return 0;
}