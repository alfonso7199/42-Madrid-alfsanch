/*
Write a program that takes two strings and displays, without doubles, the
characters that appear in either one of the strings.

The display will be in the order characters appear in the command line, and
will be followed by a \n.

If the number of arguments is not 2, the program displays \n.
*/

#include <unistd.h>

int in_both(char *printed, char c, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (printed[i] == c)
            return 1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (argc == 3)
    {
        int i = 0;
        char printed[256];
        int len = 0;
    
        while (argv[1][i])
        {
            if (!in_both(printed, argv[1][i], len))
            {
                printed[len++] = argv[1][i];
                write(1, &argv[1][i], 1);
            }
            i++;
        }
        i = 0;
        while (argv[2][i])
        {
            if (!in_both(printed, argv[2][i], len))
            {
                printed[len++] = argv[2][i];
                write(1, &argv[2][i], 1);
            }
            i++;
        }
    }
    write(1, "\n", 1);
    return (0);
}