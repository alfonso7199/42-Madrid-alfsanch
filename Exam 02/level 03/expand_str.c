/*
Write a program that takes a string and displays it with exactly three spaces
between each word, with no spaces or tabs either at the beginning or the end,
followed by a newline.

A word is a section of string delimited either by spaces/tabs, or by the
start/end of the string.

If the number of parameters is not 1, or if there are no words, simply display
a newline.
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
                {
                    write(1, "   ", 3);
                }
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
