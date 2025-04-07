/*
Write a function that converts the string argument str to an integer (type int)
and returns it.

It works much like the standard atoi(const char *str) function, see the man.

Your function must be declared as follows:

int	ft_atoi(const char *str);
*/
#include <stdio.h>
int ft_atoi(const char *str)
{
    int i = 0;
    int sign = 1;
    int result = 0;

    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        i++;
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')  
            sign = -1;
        i++;
    }
    while (str[i] && (str[i] >= '0' && str[i] <= '9'))
    {
        result *= 10;
        result += str[i] - '0';
        i++;
    }
    return (sign * result);
}
int main(void)
{
    printf("%d\n", ft_atoi("   -123")); // -123
    printf("%d\n", ft_atoi("42"));      // 42
    printf("%d\n", ft_atoi("  +7"));    // 7
}