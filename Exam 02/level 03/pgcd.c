/*
Write a program that takes two strings representing two strictly positive
integers that fit in an int.

Display their highest common denominator followed by a newline (It's always a
strictly positive integer).

If the number of parameters is not 2, display a newline.
*/
#include <stdio.h>
#include <stdlib.h>


int main(int ac, char **av)
{

    if (ac == 3)
    {
        int number1 = atoi(av[1]);
        int number2 = atoi(av[2]);
        
        if (number1 > 0 && number2 > 0)
        {
            while (number1 != number2)
            {
                if (number1 > number2)
                    number1 = number1 - number2;
                else
                    number2 = number2 - number1;
            }
            printf("%d", number1);
        }
    }
    printf("\n");
}