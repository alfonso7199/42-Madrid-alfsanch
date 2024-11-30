#include "ft_printf.h"

int ft_convert_string(const char *str)
{
    int len = 0;

    if (!str)
        str = "(null)";
    while (str[len])
        len++;
    write(1, str, len);
    return len;
}
