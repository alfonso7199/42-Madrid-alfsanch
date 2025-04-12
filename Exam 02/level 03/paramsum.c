/*
Write a program that displays the number of arguments passed to it, followed by
a newline.

If there are no arguments, just display a 0 followed by a newline.
*/
#include <unistd.h>

void ft_putnbr(int i)
{
    if (i > 9)
        ft_putnbr(i / 10);
    write(1, &"0123456789"[i % 10], 1);
}

int main(int argc, char **argv)
{
    (void) argv;
    ft_putnbr(argc - 1);
    write(1, "\n", 1);
    
    return (0);
}