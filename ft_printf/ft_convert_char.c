#include "ft_printf.h"

int ft_convert_char(char c)
{
    write(1, &c, 1);
    return 1;
}
