/*
Write a program that takes three strings:
- The first and the third one are representations of base-10 signed integers
  that fit in an int.
- The second one is an arithmetic operator chosen from: + - * / %

The program must display the result of the requested arithmetic operation,
followed by a newline. If the number of parameters is not 3, the program
just displays a newline.

You can assume the string have no mistakes or extraneous characters. Negative
numbers, in input or output, will have one and only one leading '-'. The
result of the operation fits in an int.
*/
#include <unistd.h>
#include <stdlib.h>

void ft_putnbr (int nbr)
{
    if (nbr < 0)
    {
        write(1, "-", 1);
        nbr = -nbr;
    }
    if (nbr >= 10)
        ft_putnbr(nbr/10);
    write(1, &"0123456789"[nbr % 10], 1);
}
int main(int argc, char *argv[])
{
    if (argc == 4)
    {
        int number1 = atoi(argv[1]);
        int number2 = atoi(argv[3]);

        if (argv[2][0] == '+')
            ft_putnbr(number1 + number2);
        else if (argv[2][0] == '-')
            ft_putnbr(number1 - number2);
        else if (argv[2][0] == '*')
            ft_putnbr(number1 * number2);
        else if (argv[2][0] == '/')
            ft_putnbr(number1 / number2);
        else if (argv[2][0])
            ft_putnbr(number1 % number2);          
    }
    write (1, "\n", 1);

}