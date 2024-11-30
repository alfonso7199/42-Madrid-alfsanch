#include "ft_printf.h"

static void ft_putnbr_base(unsigned long num, char *base, int *count)
{
    if (num >= 16)
        ft_putnbr_base(num / 16, base, count);
    *count += write(1, &base[num % 16], 1);
}

int ft_convert_pointer(void *ptr)
{
    int count = 0;

    count += write(1, "0x", 2);
    if (!ptr)
        count += write(1, "0", 1);
    else
        ft_putnbr_base((unsigned long)ptr, "0123456789abcdef", &count);
    return count;
}
