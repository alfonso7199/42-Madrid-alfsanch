/*
Write a program that takes two strings and displays, without doubles, the
characters that appear in both strings, in the order they appear in the first
one.

The display will be followed by a \n.

If the number of arguments is not 2, the program displays \n.
*/
void ft_printed(char *str, char c, int pos)
{
    int i = 0;
    while (i < pos)
    {
        if (str[i] == c)
            return (1);
        i++;    
    }
    return (0);
}
void search_C (char *str, char c)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}

int main(int argc, char **argv)
{
    int i = 0;

    if (argc == 3)
    {
        while (argv[1][i])
        {
            if (char_in_str(argv[2], argv[1][i]) &&
                !already_printed(argv[1], argv[1][i], i))
            {
                write(1, &argv[1][i], 1);
            }
            i++;
        }
    }
    write(1, "\n", 1);
    return (0);
}