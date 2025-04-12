/*
Write a program that takes a positive integer as argument and displays the sum
of all prime numbers inferior or equal to it followed by a newline.

If the number of arguments is not 1, or the argument is not a positive number,
just display 0 followed by a newline.

Yes, the examples are right.
*/
#include <unistd.h>

void ft_putnbr(int i)
{
    if (i > 9)
        ft_putnbr(i / 10);
    write(1, &"0123456789"[i % 10], 1);
}

int is_prime(int n)
{
    int i;

    if (n < 2)
        return (0);
    i = 2;
    while (i * i <= n)
    {
        if (n % i == 0)
            return (0);
        i++;
    }
    return (1);
}

int ft_atoi(char *str)
{
    int i;
    int result;

    i = 0;
    result = 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (-1);
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return (result);
}

int	main(int argc, char **argv)
{
	int nb;
	int i;
	int sum;

	if (argc == 2)
	{
		nb = ft_atoi(argv[1]);
		if (nb <= 0)
		{
			write(1, "0\n", 2);
			return (0);
		}
		i = 2;
		sum = 0;
		while (i <= nb)
		{
			if (is_prime(i))
				sum += i;
			i++;
		}
		ft_putnbr(sum);
		write(1, "\n", 1);
	}
	else
		write(1, "0\n", 2);
	return (0);
}