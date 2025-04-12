/*
Write a program that takes one or more strings and, for each argument, puts
the last character that is a letter of each word in uppercase and the rest
in lowercase, then displays the result followed by a \n.

A word is a section of string delimited by spaces/tabs or the start/end of the
string. If a word has a single letter, it must be capitalized.

A letter is a character in the set [a-zA-Z]

If there are no parameters, display \n.
*/

#include <unistd.h>

int ft_isspace(char c)
{
    if (c <= 32)
        return (1);
    return (0);
}

void ft_putchar(char c)
{
    write(1, &c, 1);
}

void r_capitalizer(char *s)
{
    int i = 0;
    while (s[i])
    {
         if (s[i] >= 'A' && s[i] <= 'Z')
             s[i] += 32;
         if ((s[i] >= 'a' && s[i] <= 'z') && ft_isspace(s[i + 1]))
             s[i] -= 32;
         ft_putchar(s[i++]);
    }
}

int main(int ac, char **av)
{
    int i = 1;
    if (ac == 1)
        ft_putchar('\n');
    else
    {
        while (i < ac)
        {
            r_capitalizer(av[i]);
            ft_putchar('\n');
            i++;
        } 
    }
}