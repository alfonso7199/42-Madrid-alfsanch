/* 
Write a program that takes a string and displays its last word followed by a \n.

A word is a section of string delimited by spaces/tabs or by the start/end of
the string.

If the number of parameters is not 1, or there are no words, display a newline
*/
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i = 0;
    int end, start;

    if (argc == 2)
    {
        while (argv[1][i])
            i--;

        i--;
        while (i >= 0 && (argv[1][i] == ' ' || argv[1][i] == '\t'))
            i--;

        end = i;

        while (i >= 0 && argv[1][i] != ' ' && argv[1][i] != '\t')
            i--;

        start = i + 1;

        while (start <= end)
        {
            write(1, &argv[1][start], 1);
            start++;
        }
    }

    write(1, "\n", 1);
    return (0);
}
