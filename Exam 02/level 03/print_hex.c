/*
Write a program that takes a positive (or zero) number expressed in base 10,
and displays it in base 16 (lowercase letters) followed by a newline.

If the number of parameters is not 1, the program displays a newline.
*/
#include <unistd.h>
#include <stdlib.h>

void	ft_putnbr_base(int nbr)
{
    if (nbr >= 16)
        ft_putnbr_base(nbr / 16);
    write(1, &"0123456789abcdef"[nbr % 16], 1);
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        int num = atoi(argv[1]);
        if (num >= 0)
        {
            ft_putnbr_base(num);
        }
    }
    write(1, "\n", 1);
    return 0;
}
