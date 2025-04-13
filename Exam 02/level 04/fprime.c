/*
Write a program that takes a positive int and displays its prime factors on the
standard output, followed by a newline.

Factors must be displayed in ascending order and separated by '*', so that
the expression in the output gives the right result.

If the number of parameters is not 1, simply display a newline.

The input, when there is one, will be valid.
*/

#include <stdlib.h>
#include <stdio.h> 

static void	ft_prime(int number)
{
	static int	prime;

	prime = 2;
	if (number == 1)
	{
		printf("1");
		return ;
	}
	while (prime <= number)
	{
		if ((number % prime) == 0x0)
		{
			printf("%d", prime);
			if (number != prime)
				printf("*");
			number /= prime;
		}
		else
			prime++;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 2)
		ft_prime(atoi(argv[1]));
	printf("\n");
	return (EXIT_SUCCESS);
}