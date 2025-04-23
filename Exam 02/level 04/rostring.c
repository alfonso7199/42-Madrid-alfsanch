#include <unistd.h>

int is_space(char c)
{
    return (c == ' ' || c == '\t');
}

void rostring(char *str)
{
    int i = 0;
    int word_started = 0;
    int first_start = 0;
    int first_len = 0;

    while (is_space(str[i]))
        i++;

    first_start = i;
    while (str[i] && !is_space(str[i]))
    {
        first_len++;
        i++;
    }

    while (str[i])
    {
        while (is_space(str[i]))
            i++;
        if (str[i])
        {
            if (word_started)
                write(1, " ", 1);
            while (str[i] && !is_space(str[i]))
            {
                write(1, &str[i], 1);
                i++;
            }
            word_started = 1;
        }
    }
    if (first_len)
    {
        if (word_started)
            write(1, " ", 1);
        write(1, &str[first_start], first_len);
    }
}

int main(int argc, char *argv[])
{
    if (argc == 2)
        rostring(argv[1]);
    write(1, "\n", 1);
    return 0;
}
