/*
Write a program that takes a string, and displays the string in reverse
followed by a newline.

If the number of parameters is not 1, the program displays a newline.
*/
#include <unistd.h>

int main(int ac, char *av[])
{
    int i;

    i = 0;
    if (ac == 2)
    {
        while (av[1][i])
            i++;
        while (i > 0)
        {
            write(1, &av[1][i], 1);
            i--;
        }

    }
    else {
        write(1, "\n",1);
    }
}