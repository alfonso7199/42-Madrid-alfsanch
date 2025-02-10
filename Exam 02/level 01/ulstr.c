/*
Write a program that takes a string and reverses the case of all its letters.
Other characters remain unchanged.

You must display the result followed by a '\n'.

If the number of arguments is not 1, the program displays '\n'.
*/

#include <unistd.h>

int main(int ac, char *av[])
{
    int i;

    i = 0;
    if (ac == 2)
    {
        while (av[1][i])
        {
            if (av[1][i] >= 'A' && av[1][i] <= 'Y' || av[1][i] >= 'a' && av[1][i] <= 'y'  )
            {
                av[1][i] += 1;
            }
            else if (av[1][i] == 'Z' || av[1][i] == 'z')
            {
                av[1][i]  -= 25;
            }
            write (1, &av[1][i], 1);
            i++;
        }
    }
    else {
        write(1, "\n",1);
    }
}