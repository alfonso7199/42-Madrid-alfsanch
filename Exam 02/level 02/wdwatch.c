/*
Write a program that takes two strings and checks whether it's possible to
write the first string with characters from the second string, while respecting
the order in which these characters appear in the second string.

If it's possible, the program displays the string, followed by a \n, otherwise
it simply displays a \n.

If the number of arguments is not 2, the program displays a \n.
*/
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc == 3)
    {
        char *s1 = argv[1];
        char *s2 = argv[2];
        int i = 0;
        int j = 0;
    
        while (s1[i] && s2[j])
        {
            if (s1[i] == s2[j])
                i++;
            j++;
        }
    
        if (s1[i] == '\0')
        {
            i = 0;
            while (s1[i])
                write(1, &s1[i++], 1);
        }
    }
    write(1, "\n", 1);
    return (0);
}