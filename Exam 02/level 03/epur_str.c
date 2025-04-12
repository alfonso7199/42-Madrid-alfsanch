/*
Write a program that takes a string, and displays this string with exactly one
space between words, with no spaces or tabs either at the beginning or the end,
followed by a \n.

A "word" is defined as a part of a string delimited either by spaces/tabs, or
by the start/end of the string.

If the number of arguments is not 1, or if there are no words to display, the
program displays \n.
*/
#include <unistd.h>

int is_space(char c)
{
    return (c == ' ' || c == '\t');
}

int main(int argc, char **argv)
{
    int i;
    int word_started;

    if (argc == 2)
    {
        i = 0;
        word_started = 0;
        while (argv[1][i])
        {
            while (is_space(argv[1][i]))
                i++;
            if (argv[1][i])
            {
                if (word_started)
                    write(1, " ", 1);
                while (argv[1][i] && !is_space(argv[1][i]))
                {
                    write(1, &argv[1][i], 1);
                    i++;
                }
                word_started = 1;
            }
        }
    }

    write(1, "\n", 1);
    return (0);
}
