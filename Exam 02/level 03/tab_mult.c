/*
Write a program that displays a number's multiplication table.

The parameter will always be a strictly positive number that fits in an int,
and said number times 9 will also fit in an int.

If there are no parameters, the program displays \n.
*/
#include <unistd.h>
int ft_atoi(char *s)
{
    int res = 0;
    int i = 0;
    while (s[i] >= '0' && s[i] <= '9')
    {
        res *= 10;
        res += s[i] - '0';
        i++;
    }
    return res;
}

void ft_putnbr(int i)
{
    if (i > 9)
        ft_putnbr(i / 10);
    write(1, &"0123456789"[i % 10], 1);
}
int main(int ac, char **av)
{
    if (ac == 2)
    {
        int i = 1;
        int n = ft_atoi(av[1]);
        while (i < 10)
        {
            ft_putnbr(i);
            write(1, " x ", 3);
            ft_putnbr(n);
            write(1, " = ", 3);
            ft_putnbr(i * n);
            write(1, "\n", 1);
            i++;
        }
    }
    write(1, "\n", 1);
    return (0);
}