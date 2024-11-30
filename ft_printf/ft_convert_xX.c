#include "ft_printf.h"

static void ft_putnbr_base(unsigned int num, char *base, int *count)
{
    if (num >= 16)
        ft_putnbr_base(num / 16, base, count);
    *count += write(1, &base[num % 16], 1);
}

int ft_convert_xX(unsigned int num, char format)
{
    int count = 0;
    char *base;

    if (format == 'x')
        base = "0123456789abcdef";
    else
        base = "0123456789ABCDEF";
    ft_putnbr_base(num, base, &count);
    return count;
}
