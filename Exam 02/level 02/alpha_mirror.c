/* 
Write a program called alpha_mirror that takes a string and displays this string
after replacing each alphabetical character by the opposite alphabetical
character, followed by a newline.

'a' becomes 'z', 'Z' becomes 'A'
'd' becomes 'w', 'M' becomes 'N'

and so on.

Case is not changed.

If the number of arguments is not 1, display only a newline.
*/
#include <unistd.h>

int main(int ac, char *av[])
{
    int posf;
    int i;

    i = 0;
    posf = 0;
    if (ac == 2){
        while (av[1][i]) 
        {
            if (av[1][i] >= 'A' && av[1][i] <= 'Z')
            {
                posf = 'A' + ('Z' - av[1][i]);
            }
            else if (av[1][i] >= 'a' && av[1][i] <= 'z')
            {
                posf = 'a' + ('z' - av[1][i]);
            }
            else 
            {
                posf = av[1][i];
            }
            write (1, &posf, 1);
            i++;
        }
    }
    write (1, "\n", 1);
}