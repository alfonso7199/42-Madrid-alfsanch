/*
Write a function that takes an int and converts it to a null-terminated string.
The function returns the result in a char array that you must allocate.

Your function must be declared as follows:

char	*ft_itoa(int nbr);
*/
#include <stdio.h>	//For printf
#include <stdlib.h> //For malloc

static int ft_length(long number)
{
	int length;

	length = 0;
	if (number == 0)
		return (1);
	if (number < 0)
	{
		number *= -1;
		length++;
	}
	while (number > 0)
	{
		number /= 10;
		length++;
	}
	return (length);
}

char *ft_itoa(int nbr)
{
	int length;
	long number;
	char *string;

	number = nbr;
	length = ft_length(number);
	string = ((char *)malloc(length + 1));
	if (!string)
		return (NULL);
	string[length] = '\0';
	if (number == 0)
		string[0] = '0';

	if (number < 0)
	{
		string[0] = '-';
		number = -number;
	}
	while (number)
	{
		string[--length] = (number % 10) + '0';
		number /= 10;
	}

	return (string);
}